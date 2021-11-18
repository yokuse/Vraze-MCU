#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ESP8266.h>
#include <UART_Driver.h>
#include <math.h>

/* Global Definitions */
#define CAR_WAITING_INSTRUCTION     0x1
#define CAR_RECEIVED_INSTRUCTION    0x2

#define CAR_ENGINE_ON               0x1
#define CAR_ENGINE_OFF              0x0
#define CAR_WHEEL_STOP              0x0
#define CAR_WHEEL_FORWARD           0x1
#define CAR_WHEEL_BACKWARD          0x2
#define CAR_WHEEL_LEFT              0x5
#define CAR_WHEEL_BACKWARD_LEFT     0x6
#define CAR_WHEEL_RIGHT             0x9
#define CAR_WHEEL_BACKWARD_RIGHT    0xA
#define MIN_DISTANCE                15.0f
#define TICKPERIOD                  1000

const uint32_t RPM = 60;

/******************************************************************************
 * Global Variables
 *
 * engineState          - Stores the State of the Car Engine
 * rightNotchesDetected      - Stores the number of notches detected
 * instructionBuffer    - A buffer to store all the instructions
 *******************************************************************************/
volatile uint32_t engineState = CAR_ENGINE_OFF;

/* position of the encoder*/
volatile uint32_t rightNotchesDetected = 0;
volatile uint32_t leftNotchesDetected = 0;
volatile uint32_t notches = 40;     //2 rounds
volatile uint32_t timeSeconds = 0;

volatile float leftSpeed = 0;
volatile float rightSpeed = 0;

volatile float leftRPM = 0;
volatile float rightRPM = 0;

volatile float leftError = 0;
volatile float rightError = 0;

float errorTl;
float errorTr;
float lastErrorL;
float lastErrorR;
float proportionL;
float proportionR;
float integralL;
float integralR;
float derivativeL;
float derivativeR;

void getPIDOutput(uint32_t);

volatile float speed = 0.0f;
uint32_t wheelDirection = CAR_WHEEL_STOP;
uint32_t SR04IntTimes;

//this instructions buffer holds all instructions yay
char *instructionBuffer;
uint8_t wifiState = CAR_ENGINE_ON;
// -------------------------------------------------------------------------------------------------------------------
/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
    10000,
    TIMER_A_CAPTURECOMPARE_REGISTER_1,
    TIMER_A_OUTPUTMODE_RESET_SET,
    0
};

Timer_A_PWMConfig pwmConfig2 =
{
    TIMER_A_CLOCKSOURCE_SMCLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
    10000,
    TIMER_A_CAPTURECOMPARE_REGISTER_2,
    TIMER_A_OUTPUTMODE_RESET_SET,
    0
};

/* Set Timer to calculate speed*/
const Timer_A_UpModeConfig upConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_1,         // SMCLK/12 = 2MHz
    1000,                                   // 10000 tick period
    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,     // Enable CCR0 interrupt
    TIMER_A_DO_CLEAR                        // Clear value
};

const Timer_A_ContinuousModeConfig ContmConfig =
{
    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
    TIMER_A_CLOCKSOURCE_DIVIDER_1,          // SMCLK/8 = 3MHz
    TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
    TIMER_A_DO_CLEAR
};

const Timer_A_UpModeConfig upConfigEncoder =
{
    TIMER_A_CLOCKSOURCE_ACLK,
    TIMER_A_CLOCKSOURCE_DIVIDER_1,
    32678,                           // 1 second timer
    TIMER_A_TAIE_INTERRUPT_DISABLE,
    TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,
    TIMER_A_DO_CLEAR
};

eUSCI_UART_ConfigV1 UART2Config =
{
    EUSCI_A_UART_CLOCKSOURCE_SMCLK, 13, 0, 37,
    EUSCI_A_UART_NO_PARITY,
    EUSCI_A_UART_LSB_FIRST,
    EUSCI_A_UART_ONE_STOP_BIT,
    EUSCI_A_UART_MODE,
    EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
};

/**
 * Methods
 **/
void Initialise_IO(void);
void Initialise_CarMotor(void);
void Initialise_EspUART(void);
void Initialise_Encoder(void);
void setWheelDirection(uint32_t dir);
void checkForObstacle(void);

void Initialise_TimerA1(void);

static void Delay(uint32_t loop);

void Initalise_HCSR04(void);
static uint32_t getHCSR04Time(void);
float getHCSR04Distance(void);
void clearCounters(void);
// -------------------------------------------------------------------------------------------------------------------


void main()
{

    /* Stop Watchdog Timer */
    MAP_WDT_A_holdTimer();
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_3);
    /* Initialise Engine State, Wifi State & Wheel Direction */
    engineState = CAR_ENGINE_OFF; //Initialise Car Engine State to OFF
    wheelDirection = CAR_WHEEL_STOP;

    Initialise_IO();
    Initialise_CarMotor();
    Initialise_Encoder();
    //Initalise_HCSR04();
    Initialise_TimerA1();
    Initialise_EspUART();

    /* Enabling interrupts and starting the watchdog timer */
    Interrupt_enableInterrupt(INT_PORT1);
    Interrupt_enableInterrupt(INT_PORT2);
    //Interrupt_enableSleepOnIsrExit();
    Interrupt_enableMaster();
    //Timer_A_startCounter(TIMER_A1_BASE, TIMER_A_UP_MODE);
    /* Program's loop */
    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
    while (1)
    {
        while (ESP8266_WaitForAnswer(200))
        {
            // state 2 for instructions receive, please handle
            wifiState = CAR_RECEIVED_INSTRUCTION;
        }
        if (wifiState == CAR_RECEIVED_INSTRUCTION)
        {
            //Get the engine started
            engineState = CAR_ENGINE_ON;

            uint16_t i = 0;
            char c;
            char temp[2048];
            //handle instructions here
            instructionBuffer = ESP8266_GetBuffer();
            instructionBuffer = strtok(instructionBuffer, ":");
            instructionBuffer = strtok(NULL, ":");
            //we have to str cpy cannot just use sizeof(char ptr) cause its not accurate
            strcpy(temp, instructionBuffer);
            uint16_t str_len = strlen(temp);
            // temporary loop to loop through string to read instructions
            for (i; temp[i]; i++)
            {
                c = temp[i];
                if (c == 'F')
                {
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                    if (engineState == CAR_ENGINE_ON)
                    {
                        setWheelDirection(CAR_WHEEL_FORWARD);
                        Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                        while (leftNotchesDetected < 40 && rightNotchesDetected < 40)
                        {
                            getPIDOutput(45);
                        }

                        pwmConfig.dutyCycle = 0;
                        pwmConfig2.dutyCycle = 0;
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
                        Timer_A_stopTimer(TIMER_A1_BASE);
                        clearCounters();

                    }
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                }
                else if (c == 'B')
                {
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                    if (engineState == CAR_ENGINE_ON)
                    {
                        setWheelDirection(CAR_WHEEL_BACKWARD);
                        Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                        while(leftNotchesDetected < 40 && rightNotchesDetected < 40)
                        {
                            getPIDOutput(45);
                        }
                        pwmConfig.dutyCycle = 0;
                        pwmConfig2.dutyCycle = 0;
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
                        Timer_A_stopTimer(TIMER_A1_BASE);
                        clearCounters();
                    }
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                }
                else if (c == 'R')
                {
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                    if (engineState == CAR_ENGINE_ON)
                    {
                        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
                        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);

                        //Right Wheel
                        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
                        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
                        //setWheelDirection(CAR_WHEEL_LEFT);
                        Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                        while(leftNotchesDetected < 10 && rightNotchesDetected < 10)
                        {
                            getPIDOutput(12);
                        }
                        pwmConfig.dutyCycle = 0;
                        pwmConfig2.dutyCycle = 0;
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
                        Timer_A_stopTimer(TIMER_A1_BASE);
                        clearCounters();
                    }
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                }
                else if (c == 'L')
                {
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                    if (engineState == CAR_ENGINE_ON)
                    {
                        Timer_A_startCounter(TIMER_A1_BASE,TIMER_A_UP_MODE);
                        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
                        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

                        //Right Wheel
                        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
                        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
                        //setWheelDirection(CAR_WHEEL_RIGHT);
                        while(leftNotchesDetected < 10 && rightNotchesDetected < 10)
                        {
                            getPIDOutput(12);
                        }
                        pwmConfig.dutyCycle = 0;
                        pwmConfig2.dutyCycle = 0;
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
                        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
                        Timer_A_stopTimer(TIMER_A1_BASE);
                        clearCounters();
                    }
                    GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
                }
            }

        }
        engineState = CAR_ENGINE_OFF;

        //Turn LED2 to RED when Car Engine State is OFF
        //GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
        //GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);

        wifiState = CAR_WAITING_INSTRUCTION;
        // Go back to low power mode after handling all interrupts
        PCM_gotoLPM0();
    }
}

void getPIDOutput(uint32_t targetNotch)
{
    float kp = 0.15;
    float ki = 0.15;
    float kd = 0.15;

    float currentL = 0;
    float currentR = 0;

    float targetRPM = 120;
    float targetNotches = targetNotch;

    float minDiff = 10;

    //float errorL = targetRPM - leftRPM;
    //float errorR = targetRPM - rightRPM;

    __delay_cycles(5000);
    float errorL = targetNotches - leftNotchesDetected;
    float errorR = targetNotches - rightNotchesDetected;

    if (errorL < minDiff && errorL != 0)
    {
        errorTl += errorL;
    }
    else
    {
        errorTl = 0;
    }
    if (errorR < minDiff && errorR != 0)
    {
        errorTr += errorR;
    }
    else
    {
        errorTr = 0;
    }
    if (errorTl > 50/ki) { //Cant get any higher than error 50, maybe maximum adjustment value?
        errorTl = 50/ki;
    }
    if (errorTr > 50/ki)
    {
        errorTr = 50/ki;
    }
    if (errorL == 0)  //If error = 0, everything shut off, else starts accumulating again
    {
        derivativeL = 0;
    }
    if (errorR == 0)
    {
        derivativeR = 0;
    }


    /* PID CALCULATIONS*/
    proportionL = errorL * kp;
    proportionR = errorR * kp;

    integralL = errorTl * ki; //Low value of proportion might not be enough to move robot so need integral (cumulated error)
    integralR = errorTr * ki; //Eventually the integral value will be big enough to move the robot

    derivativeL = (errorL - lastErrorL) * kd; //Rate of change of error
    derivativeR = (errorR - lastErrorR) * kd; //To keep in check rest of the loop
    //if we approach target really fast and error is changing quickly, means in danger of overshooting the target
    //Used to slow us down(?), hopefully negative value so will contribute negatively to motor value

    //Update last errors
    lastErrorL = errorL;
    lastErrorR = errorR;

    //Value to be sent to the motors
    currentL = (proportionL + integralL + derivativeL) * 10000;
    currentR = (proportionR + integralR + derivativeR) * 10000;

    //Adjust PWM
    pwmConfig.dutyCycle = currentR;
    pwmConfig2.dutyCycle = currentL;
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
    Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);

}

void clearCounters(void)
{
    Timer_A_clearTimer(TIMER_A1_BASE);
    rightNotchesDetected = 0;
    timeSeconds = 0;
    leftNotchesDetected = 0;
    leftSpeed = 0;
    rightSpeed = 0;
    leftRPM = 0;
    rightRPM = 0;
    leftError = 0;
    rightError = 0;
    errorTl = 0;
    errorTr = 0;
    lastErrorL = 0;
    lastErrorR = 0;
    proportionL = 0;
    proportionR = 0;
    integralL = 0;
    integralR = 0;
    derivativeL = 0;
    derivativeR = 0;
}

/****************** Interrupt Handlers ******************/
void PORT1_IRQHandler(void)
{
    uint32_t status_for_switch1;

    status_for_switch1 = MAP_GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1); //get status of switch 1's interrupt flag

    if (status_for_switch1 & GPIO_PIN1) //Switch 1 (P1.1) On/Off Car Engine
    {
        // Placeholder interrupt to handle and send data, can be a function for when esp wants to send data, but
        // if msp is in low pwr mode then need interrupt first, probs need to call the func in the interrupt
        // or just apply send logic to that interrupt
        char dataSend[] = "debo\r\n\r\n";
        uint32_t t = sizeof(dataSend) - 1;
        ESP8266_SendData(dataSend, t);

        MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);

        MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status_for_switch1);

    }
}

void PORT2_IRQHandler(void)
{
    uint32_t status;
    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);

    if (status & GPIO_PIN7)
    {
        rightNotchesDetected += 1;
        GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN7);
    }
    if (status & GPIO_PIN6)
    {
        leftNotchesDetected += 1;
        GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN6);
    }
}



void TA1_0_IRQHandler(void)
{
    // Increment global variable (count number of interrupt occurred)
    timeSeconds += 1;
    /* RPM*/
    leftRPM = ((leftNotchesDetected/timeSeconds)/20.0)*60;
    rightRPM = ((rightNotchesDetected/timeSeconds)/20.0)*60;

    // Clear interrupt flag
    Timer_A_clearCaptureCompareInterrupt(TIMER_A1_BASE, TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

// -------------------------------------------------------------------------------------------------------------------

void Initialise_TimerA1()
{
    Timer_A_configureUpMode(TIMER_A1_BASE, &upConfigEncoder);
    Interrupt_enableInterrupt(INT_TA1_0);
    Timer_A_clearTimer(TIMER_A1_BASE);
}

void Initialise_IO()
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1,
    GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1,
    GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN4);

    //Set Output Pin for LEDs (P1.0, P2.0, P2.1, P2.2)
    GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN2);

    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN2);
}

void Initialise_CarMotor()
{
    /* Configuring P4.4 and P4.5 as Output. P2.4 as peripheral output for PWM and P1.1 for button interrupt */
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN4,
    GPIO_PRIMARY_MODULE_FUNCTION);

    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setAsOutputPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
    GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
    GPIO_setAsPeripheralModuleFunctionOutputPin(GPIO_PORT_P2, GPIO_PIN5,
    GPIO_PRIMARY_MODULE_FUNCTION);
}

void Initialise_EspUART(void)
{

    /*Ensure MSP432 is Running at 24 MHz*/
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(
            GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3,
            GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A2_BASE, &UART2Config);
    MAP_UART_enableModule(EUSCI_A2_BASE);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);

    /* switch 1.1 api post to thinkspeak test*/
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1,
    GPIO_LOW_TO_HIGH_TRANSITION);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /*Reset GPIO of the ESP8266*/
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);

    /* Reset ESP8266 to prevent timeout errors*/
    ESP8266_HardReset();
    __delay_cycles(48000000);
    UART_Flush(EUSCI_A2_BASE);

    /* Configure to start ESP8266 webserver*/
    ESP8266_ChangeMode1();
    //ESP8266_DisconnectToAP();
    //ESP8266_ConnectToAP("Reuben","lol12345678");
    //ESP8266_ConnectToAP("CHONG_Fam","ibeeciejie");
    //__delay_cycles(48000000);
    ESP8266_EstablishConnection('0', TCP, "192.168.157.22", "5000");
    //ESP8266_EstablishConnection('0', TCP, "172.20.10.2", "5000");

}

void Initialise_Encoder(void)
{
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN6, GPIO_LOW_TO_HIGH_TRANSITION);
    GPIO_interruptEdgeSelect(GPIO_PORT_P2, GPIO_PIN7, GPIO_LOW_TO_HIGH_TRANSITION);
    /* Need extra 3v3, so use GPIO to supply the 3v3*/
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN4);
    GPIO_setAsOutputPin(GPIO_PORT_P5, GPIO_PIN7);
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN4);
    GPIO_setOutputHighOnPin(GPIO_PORT_P5, GPIO_PIN7);

    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, GPIO_PIN7);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN6);
    GPIO_enableInterrupt(GPIO_PORT_P2, GPIO_PIN7);

}

void setWheelDirection(uint32_t dir)
{
    wheelDirection = dir;

    if (dir & CAR_WHEEL_FORWARD) //Forward
    {
        __delay_cycles(3000);
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

        //Right Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_BACKWARD) //Backward
    {
        __delay_cycles(3000);
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);

        //Right Wheel
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_LEFT)
    {
        __delay_cycles(3000);
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);

        //Right Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_RIGHT)
    {
        __delay_cycles(3000);
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

        //Right Wheel
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }

}

void checkForObstacle(void)
{
    Delay(3000);
    /* Obtain distance from HCSR04 sensor and check if its less then minimum distance */
    if ((getHCSR04Distance() < MIN_DISTANCE))
        setWheelDirection(CAR_WHEEL_STOP);
    else
        setWheelDirection(CAR_WHEEL_FORWARD);
}
// -------------------------------------------------------------------------------------------------------------------

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++);
}

// -------------------------------------------------------------------------------------------------------------------

void Initalise_HCSR04(void)
{
    /* Timer_A UpMode Configuration Parameter */


    int a = CS_getSMCLK();

    /* Configuring P3.6 as Output */
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);                        //
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);                      //

    GPIO_setAsInputPinWithPullDownResistor(GPIO_PORT_P3, GPIO_PIN7);

    /* Configuring Timer_A0 for Up Mode */
    Timer_A_configureUpMode(TIMER_A0_BASE, &upConfig);

    /* Enabling interrupts and starting the timer */
    Interrupt_enableInterrupt(INT_TA0_0);
    //Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    //Timer_A_stopTimer(TIMER_A0_BASE);
    Timer_A_clearTimer(TIMER_A0_BASE);

}

// -------------------------------------------------------------------------------------------------------------------

void TA0_0_IRQHandler(void)
{
    /* Increment global variable (count number of interrupt occurred) */
    SR04IntTimes++;

    /* Clear interrupt flag */
    Timer_A_clearCaptureCompareInterrupt(TIMER_A0_BASE,
    TIMER_A_CAPTURECOMPARE_REGISTER_0);
}

// -------------------------------------------------------------------------------------------------------------------

static uint32_t getHCSR04Time(void)
{
    uint32_t pulsetime = 0;

    /* Number of times the interrupt occurred (1 interrupt = 1000 ticks)    */
    pulsetime = SR04IntTimes * TICKPERIOD;

    /* Number of ticks (between 1 to 999) before the interrupt could occur */
    pulsetime += Timer_A_getCounterValue(TIMER_A0_BASE);

    /* Clear Timer */
    Timer_A_clearTimer(TIMER_A0_BASE);

    Delay(3000);

    return pulsetime;
}

// -------------------------------------------------------------------------------------------------------------------

float getHCSR04Distance(void)
{
    uint32_t pulseduration = 0;
    float calculateddistance = 0;

    /* Generate 10us pulse at P3.6 */
    GPIO_setOutputHighOnPin(GPIO_PORT_P3, GPIO_PIN6);
    Delay(30);
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);

    /* Wait for positive-edge */
    while (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 0);

    /* Start Timer */
    SR04IntTimes = 0;
    Timer_A_clearTimer(TIMER_A0_BASE);
    Timer_A_startCounter(TIMER_A0_BASE, TIMER_A_UP_MODE);

    /* Detects negative-edge */
    while (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 1)
        ;

    /* Stop Timer */
    Timer_A_stopTimer(TIMER_A0_BASE);

    /* Obtain Pulse Width in microseconds */
    pulseduration = getHCSR04Time();

    /* Calculating distance in cm */
    calculateddistance = (float) pulseduration / 58.0f;

    return calculateddistance;
}

// -------------------------------------------------------------------------------------------------------------------
