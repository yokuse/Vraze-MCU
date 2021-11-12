#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include <ESP8266.h>
#include <UART_Driver.h>

/* Global Definitions */
#define CAR_WAITING_INSTRUCTION     0x1
#define CAR_RECEIVED_INSTRUCTION    0x2
#define CAR_ENGINE_ON               0x1
#define CAR_ENGINE_OFF              0x0
#define CAR_WHEEL_STOP              0x0
#define CAR_WHEEL_FORWARD           0x1
#define CAR_WHEEL_BACKWARD          0x2
#define CAR_WHEEL_FORWARD_LEFT      0x5
#define CAR_WHEEL_BACKWARD_LEFT     0x6
#define CAR_WHEEL_FORWARD_RIGHT     0x9
#define CAR_WHEEL_BACKWARD_RIGHT    0xA
#define MIN_DISTANCE                15.0f
#define TICKPERIOD                  1000

const uint32_t RPM = 60;

/******************************************************************************
 * Global Variables
 *
 * engineState          - Stores the State of the Car Engine
 * notchesDetected      - Stores the number of notches detected
 * instructionBuffer    - A buffer to store all the instructions
 *******************************************************************************/
volatile uint32_t engineState = CAR_ENGINE_OFF;
volatile uint32_t notchesDetected = 0;
volatile float speed = 0.0f;
uint32_t wheelDirection = CAR_WHEEL_STOP;
uint32_t SR04IntTimes;

//this instructions buffer holds all instructions yay
char *instructionBuffer;
uint8_t wifiStatus = CAR_ENGINE_ON;
// -------------------------------------------------------------------------------------------------------------------
/* Timer_A PWM Configuration Parameter */
Timer_A_PWMConfig pwmConfig = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                TIMER_A_CLOCKSOURCE_DIVIDER_24, 10000,
                                TIMER_A_CAPTURECOMPARE_REGISTER_1,
                                TIMER_A_OUTPUTMODE_RESET_SET, 1000 };

Timer_A_PWMConfig pwmConfig2 = {
TIMER_A_CLOCKSOURCE_SMCLK,
                                 TIMER_A_CLOCKSOURCE_DIVIDER_24, 10000,
                                 TIMER_A_CAPTURECOMPARE_REGISTER_2,
                                 TIMER_A_OUTPUTMODE_RESET_SET, 1000 };

/*
 eUSCI_UART_ConfigV1 UART0Config =
 {
 EUSCI_A_UART_CLOCKSOURCE_SMCLK,
 13,
 0,
 37,
 EUSCI_A_UART_NO_PARITY,
 EUSCI_A_UART_LSB_FIRST,
 EUSCI_A_UART_ONE_STOP_BIT,
 EUSCI_A_UART_MODE,
 EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION
 };*/

eUSCI_UART_ConfigV1 UART2Config = {
        EUSCI_A_UART_CLOCKSOURCE_SMCLK, 13, 0, 37,
        EUSCI_A_UART_NO_PARITY,
        EUSCI_A_UART_LSB_FIRST,
        EUSCI_A_UART_ONE_STOP_BIT,
        EUSCI_A_UART_MODE,
        EUSCI_A_UART_OVERSAMPLING_BAUDRATE_GENERATION };
/*
 void ESP8266_Terminal(void)
 {
 while(1)
 {
 //* variable to store channel
 uint8_t ESP_channel = 5;    //get response channel that esp is using
 char * separator = "=";

 //* call function to populate ESP buffer with data
 // getData();
 UART_Gets(EUSCI_A2_BASE, ESP8266_Buffer, 2048);
 UART_Printf(EUSCI_A0_BASE, ESP8266_Buffer);
 __delay_cycles(48000000);
 if(strstr(ESP8266_Buffer, "+IPD,0") != NULL)
 ESP_channel = 0;
 else if(strstr(ESP8266_Buffer, "+IPD,1") != NULL)
 ESP_channel = 1;
 else if(strstr(ESP8266_Buffer, "+IPD,2") != NULL)
 ESP_channel = 2;
 else if(strstr(ESP8266_Buffer, "+IPD,3") != NULL)
 ESP_channel = 3;
 else if(strstr(ESP8266_Buffer, "+IPD,4") != NULL)
 ESP_channel = 4;


 if(strstr(ESP8266_Buffer, "instructions=") != NULL)
 {
 instructionBuffer = strtok(ESP8266_Buffer, separator);
 instructionBuffer = strtok(NULL, ESP8266_Buffer);
 UART_Printf(EUSCI_A0_BASE, instructionBuffer);
 }
 if (ESP_channel != 5)
 {
 //*Data that will be sent to the HTTP server
 char HTTP_Request[] = "POST /test HTTP/1.1\r\nHost: 192.168.157.22:5000\r\nContent-Type: application/json\r\nContent-length: 11\r\n\r\n{\"test\": 3}";
 uint32_t HTTP_Request_Size = sizeof(HTTP_Request) - 1;
 ESP8266_SendData(ESP_channel, HTTP_Request, HTTP_Request_Size);
 __delay_cycles(48000000);
 UART_Printf(EUSCI_A2_BASE, "AT+CIPCLOSE=%i\r\n", ESP_channel);
 ESP_channel = 5;
 }
 }
 }
 */

void main()
{
    /*Initialize required hardware peripherals for the ESP8266*/
    /*
     MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P1, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
     MAP_UART_initModule(EUSCI_A0_BASE, &UART0Config);
     MAP_UART_enableModule(EUSCI_A0_BASE);
     MAP_UART_enableInterrupt(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
     MAP_Interrupt_enableInterrupt(INT_EUSCIA0);
     */
    /* Stop Watchdog Timer */
    MAP_WDT_A_holdTimer();

    /*Ensure MSP432 is Running at 24 MHz*/
    FlashCtl_setWaitState(FLASH_BANK0, 2);
    FlashCtl_setWaitState(FLASH_BANK1, 2);
    PCM_setCoreVoltageLevel(PCM_VCORE1);
    CS_setDCOCenteredFrequency(CS_DCO_FREQUENCY_24);

    MAP_GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P3, GPIO_PIN2 | GPIO_PIN3, GPIO_PRIMARY_MODULE_FUNCTION);
    MAP_UART_initModule(EUSCI_A2_BASE, &UART2Config);
    MAP_UART_enableModule(EUSCI_A2_BASE);
    MAP_UART_enableInterrupt(EUSCI_A2_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT);
    MAP_Interrupt_enableInterrupt(INT_EUSCIA2);

    /* switch 1.1 api post to thinkspeak test*/
    MAP_GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_interruptEdgeSelect(GPIO_PORT_P1, GPIO_PIN1, GPIO_LOW_TO_HIGH_TRANSITION);
    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
    MAP_GPIO_enableInterrupt(GPIO_PORT_P1, GPIO_PIN1);
    MAP_Interrupt_enableInterrupt(INT_PORT1);
    MAP_GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
    MAP_GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);

    /*Reset GPIO of the ESP8266*/
    GPIO_setAsOutputPin(GPIO_PORT_P6, GPIO_PIN1);

    MAP_Interrupt_enableMaster();

    /* Reset ESP8266 to prevent timeout errors*/
    ESP8266_HardReset();
    __delay_cycles(48000000);
    UART_Flush(EUSCI_A2_BASE);

    /* Configure to start ESP8266 webserver*/
    ESP8266_ChangeMode1();
    //ESP8266_EnableMultipleConnections(1);
    //ESP8266_DisconnectToAP();
    //ESP8266_ConnectToAP("Reuben","lol12345678");
    //ESP8266_ConnectToAP("CHONG_Fam","ibeeciejie");
    //__delay_cycles(48000000);
    //ESP8266_EstablishConnection('0', TCP, "192.168.157.22", "5000");
    ESP8266_EstablishConnection('0', TCP, "172.20.10.2", "5000");
    //ESP8266_startserver();

    /*Start ESP8266 serial terminal, will not return*/
    //ESP8266_Terminal();
    /* Have to do this instruction first */
    printf("Ready\n");

    /* Program's loop */
    while (1)
    {
        while (ESP8266_WaitForAnswer(200))
        {
            // state 2 for instructions receive, please handle
            wifiStatus = CAR_RECEIVED_INSTRUCTION;
        }
        if (wifiStatus == CAR_RECEIVED_INSTRUCTION)
        {
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
                //remember to change the state of the the car aft reading each char, according to the char
                c = temp[i];
                // if (c == "W")
                //printf("call while loop function");
                // when comparing the char, make sure its single quotation if not !=

                if (c == 'F')
                    printf("car is moving forward\n");
                else if (c == 'B')
                    printf("car is moving backward\n");
                else if (c == 'R')
                    printf("car is moving right\n");
                else if (c == 'L')
                    printf("car is moving left\n");
                else
                    printf("random/n");
            }
            //can start to read instructions buffer and do soft interrupts OR make function calls
            printf("%s\n", instructionBuffer);
        }
        wifiStatus = CAR_WAITING_INSTRUCTION;
        // Go back to low power mode after handling all interrupts
        PCM_gotoLPM0();
    }

}
/*
 void ESP8266_Terminal(void)
 {
 while(1)
 {
 UART_Gets(EUSCI_A0_BASE, ESP8266_Buffer, 128);
 UART_Printf(EUSCI_A2_BASE, ESP8266_Buffer);

 __delay_cycles(48000000);
 if(!ESP8266_WaitForAnswer(ESP8266_RECEIVE_TRIES))
 {
 UART_Printf(EUSCI_A0_BASE, "ESP8266 receive timeout error\r\n");
 }
 else
 {
 UART_Printf(EUSCI_A0_BASE, ESP8266_Buffer);
 }

 }
 }*/

/****************** Interrupt Handlers ******************/
void PORT1_IRQHandler(void)
{
    uint32_t status_for_switch1;

    status_for_switch1 = MAP_GPIO_getInterruptStatus(GPIO_PORT_P1, GPIO_PIN1); //get status of switch 1's interrupt flag

    if (status_for_switch1 & GPIO_PIN1) //Switch 1 (P1.1) On/Off Car Engine
    {
        //If engine is currently ON, set to OFF
        if (engineState == CAR_ENGINE_ON)
        {
            //Set Motor Duty Cycle to 0% (Off)
            pwmConfig.dutyCycle = 0;
            pwmConfig2.dutyCycle = 0;

            engineState = CAR_ENGINE_OFF;
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN1);
        }
        else if (engineState == CAR_ENGINE_OFF)
        {
            //Set Motor Duty Cycle to 10% (On)
            pwmConfig.dutyCycle = 1000;
            pwmConfig2.dutyCycle = 1000;

            engineState = CAR_ENGINE_ON;
            setWheelDirection(CAR_WHEEL_FORWARD);
            GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN0);
            GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN1);

            // Placeholder interrupt to handle and send data, can be a function for when esp wants to send data, but
            // if msp is in low pwr mode then need interrupt first, probs need to call the func in the interrupt
            // or just apply send logic to that interrupt
            char dataSend[] = "debo\r\n\r\n";
            uint32_t t = sizeof(dataSend) - 1;
            ESP8266_SendData(dataSend, t);

            MAP_GPIO_toggleOutputOnPin(GPIO_PORT_P1, GPIO_PIN0);
        }

        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    }
    else if (status_for_switch1 & GPIO_PIN4) //Switch 2 (P1.4) Change Motor Speed
    {
        if (engineState == CAR_ENGINE_ON)
        {
            if (pwmConfig.dutyCycle == 9000)
                pwmConfig.dutyCycle = 0;
            else
                pwmConfig.dutyCycle += 1000;

            if (pwmConfig2.dutyCycle == 9000)
                pwmConfig2.dutyCycle = 0;
            else
                pwmConfig2.dutyCycle += 1000;
        }
        else
        {
            pwmConfig.dutyCycle = 0;
            pwmConfig2.dutyCycle = 0;
        }

        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig);
        Timer_A_generatePWM(TIMER_A0_BASE, &pwmConfig2);
    }

    MAP_GPIO_clearInterruptFlag(GPIO_PORT_P1, status_for_switch1);

}

void PORT2_IRQHandler(void)
{
    uint32_t status; //Stores the pin that trigger the interrupt

    status = GPIO_getEnabledInterruptStatus(GPIO_PORT_P2);
    GPIO_clearInterruptFlag(GPIO_PORT_P2, status);
    notchesDetected++;
}

// -------------------------------------------------------------------------------------------------------------------

void Initialise_Switches()
{
    engineState = CAR_ENGINE_OFF; //Initialise Car Engine State to OFF
    wheelDirection = CAR_WHEEL_STOP;
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN1);
    GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P1, GPIO_PIN4);
    GPIO_clearInterruptFlag(GPIO_PORT_P1, GPIO_PIN1);
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

void setWheelDirection(uint32_t dir)
{
    wheelDirection = dir;

    if (dir & CAR_WHEEL_FORWARD) //Forward
    {
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);

        //Right Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_BACKWARD) //Backward
    {
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);

        //Right Wheel
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_FORWARD_LEFT)
    {
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN2);

        //Right Wheel
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_FORWARD_RIGHT)
    {
        //Left Wheel
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);

        //Right Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
        GPIO_setOutputHighOnPin(GPIO_PORT_P4, GPIO_PIN5);
    }
    else if (dir & CAR_WHEEL_BACKWARD_LEFT)
    {
    }
    else if (dir & CAR_WHEEL_BACKWARD_RIGHT)
    {
    }
    else
    {
        //Left Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN0);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN2);

        //Right Wheel
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN5);
        GPIO_setOutputLowOnPin(GPIO_PORT_P4, GPIO_PIN4);
    }
}

// -------------------------------------------------------------------------------------------------------------------

static void Delay(uint32_t loop)
{
    volatile uint32_t i;

    for (i = 0; i < loop; i++)
        ;
}

// -------------------------------------------------------------------------------------------------------------------

void Initalise_HCSR04(void)
{
    /* Timer_A UpMode Configuration Parameter */
    const Timer_A_UpModeConfig upConfig = {
    TIMER_A_CLOCKSOURCE_SMCLK,              // SMCLK Clock Source
            TIMER_A_CLOCKSOURCE_DIVIDER_3,          // SMCLK/3 = 1MHz
            TICKPERIOD,                             // 1000 tick period
            TIMER_A_TAIE_INTERRUPT_DISABLE,         // Disable Timer interrupt
            TIMER_A_CCIE_CCR0_INTERRUPT_ENABLE,    // Enable CCR0 interrupt
            TIMER_A_DO_CLEAR                        // Clear value
            };

    int a = CS_getSMCLK();

    /* Configuring P3.6 as Output */
    GPIO_setAsOutputPin(GPIO_PORT_P3, GPIO_PIN6);                        //
    GPIO_setOutputLowOnPin(GPIO_PORT_P3, GPIO_PIN6);                        //

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
    while (GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN7) == 0)
        ;

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
