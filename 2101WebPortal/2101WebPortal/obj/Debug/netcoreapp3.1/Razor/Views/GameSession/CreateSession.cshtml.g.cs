#pragma checksum "C:\Users\rcwww\Desktop\Y2T1\2104\Project\ict2104_carProj\2101WebPortal\2101WebPortal\Views\GameSession\CreateSession.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "d628cad7243f1197675610d9d5d026a4fc9d6fb2"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_GameSession_CreateSession), @"mvc.1.0.view", @"/Views/GameSession/CreateSession.cshtml")]
namespace AspNetCore
{
    #line hidden
    using System;
    using System.Collections.Generic;
    using System.Linq;
    using System.Threading.Tasks;
    using Microsoft.AspNetCore.Mvc;
    using Microsoft.AspNetCore.Mvc.Rendering;
    using Microsoft.AspNetCore.Mvc.ViewFeatures;
#nullable restore
#line 1 "C:\Users\rcwww\Desktop\Y2T1\2104\Project\ict2104_carProj\2101WebPortal\2101WebPortal\Views\_ViewImports.cshtml"
using Vraze;

#line default
#line hidden
#nullable disable
#nullable restore
#line 2 "C:\Users\rcwww\Desktop\Y2T1\2104\Project\ict2104_carProj\2101WebPortal\2101WebPortal\Views\_ViewImports.cshtml"
using Vraze.Models;

#line default
#line hidden
#nullable disable
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"d628cad7243f1197675610d9d5d026a4fc9d6fb2", @"/Views/GameSession/CreateSession.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"d74cd0e45e0e484cb5131bc43133c1eb3e8ce708", @"/Views/_ViewImports.cshtml")]
    public class Views_GameSession_CreateSession : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<dynamic>
    {
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_0 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "Admin", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_1 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Home", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_2 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "GameSession", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_3 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Manage", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_4 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Index", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_5 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("id", new global::Microsoft.AspNetCore.Html.HtmlString("btnBack"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_6 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("class", new global::Microsoft.AspNetCore.Html.HtmlString("btn btn-success btn-block"), global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        #line hidden
        #pragma warning disable 0649
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperExecutionContext __tagHelperExecutionContext;
        #pragma warning restore 0649
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperRunner __tagHelperRunner = new global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperRunner();
        #pragma warning disable 0169
        private string __tagHelperStringValueBuffer;
        #pragma warning restore 0169
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager __backed__tagHelperScopeManager = null;
        private global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager __tagHelperScopeManager
        {
            get
            {
                if (__backed__tagHelperScopeManager == null)
                {
                    __backed__tagHelperScopeManager = new global::Microsoft.AspNetCore.Razor.Runtime.TagHelpers.TagHelperScopeManager(StartTagHelperWritingScope, EndTagHelperWritingScope);
                }
                return __backed__tagHelperScopeManager;
            }
        }
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper;
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.FormTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper;
        private global::Microsoft.AspNetCore.Mvc.TagHelpers.RenderAtEndOfFormTagHelper __Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper;
        #pragma warning disable 1998
        public async override global::System.Threading.Tasks.Task ExecuteAsync()
        {
#nullable restore
#line 1 "C:\Users\rcwww\Desktop\Y2T1\2104\Project\ict2104_carProj\2101WebPortal\2101WebPortal\Views\GameSession\CreateSession.cshtml"
   ViewData["Title"] = "Create New Game Session"; 

#line default
#line hidden
#nullable disable
            WriteLiteral(@"

<div class=""text-center"">
    <h1 class=""display-4"">Add New Game Session</h1>
</div>
<div class=""row"">
    <div class=""col-md-12"">
        <h6>
            <nav aria-label=""breadcrumb"">
                <ol class=""breadcrumb"">
                    <li class=""breadcrumb-item"">");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "d628cad7243f1197675610d9d5d026a4fc9d6fb26277", async() => {
                WriteLiteral("Home");
            }
            );
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Controller = (string)__tagHelperAttribute_0.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_0);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Action = (string)__tagHelperAttribute_1.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_1);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral("</li>\r\n                    <li class=\"breadcrumb-item\">");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "d628cad7243f1197675610d9d5d026a4fc9d6fb27691", async() => {
                WriteLiteral("Game Sessions");
            }
            );
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Controller = (string)__tagHelperAttribute_2.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_2);
            __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Action = (string)__tagHelperAttribute_3.Value;
            __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_3);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral(@"</li>
                    <li class=""breadcrumb-item active"" aria-current=""page"">Create New Game Session</li>
                </ol>
            </nav>
        </h6>
    </div>
</div>
<div class=""col-lg-8 mx-auto mt-3"">
    <div class=""card"">
        <div class=""card-body"">
            <h2 class=""text-info"">Game Session Information</h2>
            <div id=""errorMsgAlertBox"" class=""alert alert-warning alert-dismissible fade show d-none"" role=""alert"">
                <span id=""errorMsgAlert""></span>
                <button type=""button"" class=""close"" data-dismiss=""alert"" aria-label=""Close"">
                    <span aria-hidden=""true"">&times;</span>
                </button>
            </div>
            ");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("form", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "d628cad7243f1197675610d9d5d026a4fc9d6fb29816", async() => {
                WriteLiteral(@"
                <div class=""form-group row"">
                    <label class=""col-md-3 form-label"">Access Code</label>
                    <div class=""col-sm-9"">
                        <input type=""text"" class=""form-control"" id=""tbAccessCode"" required>
                        <div id=""tbAccessCodeFeedback"" class=""custom-feedback-msg""></div>
                    </div>
                </div>
                <div class=""form-group row"">
                    <label class=""col-md-3 form-label"">Challenges</label>
                    <div class=""col-sm-9"">
                        <input type=""text"" class=""form-control"" id=""tbChallengeList"" required>
                        <small id=""challengeListHelp"" class=""form-text text-muted"">Please separate each challenge ID by ';'.</small>
                        <div id=""tbChallengeListFeedback"" class=""custom-feedback-msg""></div>
                    </div>
                </div>
                <div class=""form-group row"">
                    <label class=");
                WriteLiteral(@"""col-md-3 form-label"">Student List</label>
                    <div class=""col-sm-9"">
                        <table class=""table"">
                            <thead>
                                <tr>
                                    <th>Student Id</th>
                                    <th>Name</th>
                                    <th>Action</th>
                                </tr>
                            </thead>
                            <tbody id=""studentListTable"">
                            </tbody>
                        </table>
                        <span class=""btn btn-info btn-block"" id=""btnAddNewStudentRow"">Add New Student</span>
                        <div id=""tbStudentList"">
                            <div id=""tbStudentListFeedback"" class=""custom-feedback-msg""></div>
                        </div>
                    </div>
                </div>
                <div class=""form-group row"">
                    <div class=""col-md-6"">
               ");
                WriteLiteral("         ");
                __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "d628cad7243f1197675610d9d5d026a4fc9d6fb212259", async() => {
                    WriteLiteral("<i class=\"fas fa-sign-out-alt\"></i> Back");
                }
                );
                __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.AnchorTagHelper>();
                __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper);
                __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Action = (string)__tagHelperAttribute_4.Value;
                __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_4);
                __Microsoft_AspNetCore_Mvc_TagHelpers_AnchorTagHelper.Controller = (string)__tagHelperAttribute_0.Value;
                __tagHelperExecutionContext.AddTagHelperAttribute(__tagHelperAttribute_0);
                __tagHelperExecutionContext.AddHtmlAttribute(__tagHelperAttribute_5);
                __tagHelperExecutionContext.AddHtmlAttribute(__tagHelperAttribute_6);
                await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
                if (!__tagHelperExecutionContext.Output.IsContentModified)
                {
                    await __tagHelperExecutionContext.SetOutputContentAsync();
                }
                Write(__tagHelperExecutionContext.Output);
                __tagHelperExecutionContext = __tagHelperScopeManager.End();
                WriteLiteral("\r\n                    </div>\r\n                    <div class=\"col-md-6\">\r\n                        <button id=\"btnSubmit\" class=\"btn btn-primary btn-block\">Create</button>\r\n                    </div>\r\n                </div>\r\n            ");
            }
            );
            __Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.FormTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_FormTagHelper);
            __Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper = CreateTagHelper<global::Microsoft.AspNetCore.Mvc.TagHelpers.RenderAtEndOfFormTagHelper>();
            __tagHelperExecutionContext.Add(__Microsoft_AspNetCore_Mvc_TagHelpers_RenderAtEndOfFormTagHelper);
            await __tagHelperRunner.RunAsync(__tagHelperExecutionContext);
            if (!__tagHelperExecutionContext.Output.IsContentModified)
            {
                await __tagHelperExecutionContext.SetOutputContentAsync();
            }
            Write(__tagHelperExecutionContext.Output);
            __tagHelperExecutionContext = __tagHelperScopeManager.End();
            WriteLiteral(@"
        </div>
    </div>
</div>

<script>
    var accessCode = """";
    var challengeList = """";
    var studentList = [];

    function RemoveStudentRow(button) {
        console.log(""button:"", button);
        console.log(""this:"", $(this).parent());
        console.log(""closest tr:"", $(this).closest(""tr""));
        $(button).parent().parent().remove();
    }
    $(document).ready(function () {
        $('#errorMsgAlertBox').addClass('d-none');
        $('#errorMsgAlert').text('');

        $(""#btnAddNewStudentRow"").click(function () {
            $('#studentListTable').append('<tr class=""studentRow""><td><input type=""text"" class=""form-control tbStudentId"" placeholder=""Student Id""/></td><td><input type=""text"" class=""form-control tbStudentName"" placeholder=""Student Name""/></td><td><span class=""btn btn-danger btn-sm btnRemoveStudRow"" onclick=""RemoveStudentRow(this)"">Remove</span></td></tr>');
        });

        $('#btnSubmit').click(function (e) {
            e.preventDefault();
    ");
            WriteLiteral(@"        SubmitForm();
        });

        function StudentClass(studId, studName)
        {
            this.StudentId = studId;
            this.Name = studName;
        }

        function ValidateForm() {
            var valid = true;

            accessCode = $(""#tbAccessCode"").val();
            challengeList = $(""#tbChallengeList"").val();
            studentList = [];
            var studentRows = $("".studentRow"");
            console.log(""rows:"", studentRows);

            //Resets all feedback messages
            $("".custom-feedback-msg"").text("""");
            $("".custom-feedback-msg"").removeClass(""invalid-feedback"");

            if (accessCode === """") {
                $(""#tbAccessCode"").addClass(""is-invalid"");
                $(""#tbAccessCodeFeedback"").addClass(""invalid-feedback"");
                $(""#tbAccessCodeFeedback"").text(""Please do not leave this blank."");

                valid &= false;
            }
            else {
                valid &= true;
      ");
            WriteLiteral(@"          $(""#tbAccessCode"").removeClass(""is-invalid"");
            }

            if (challengeList === """") {
                $(""#tbChallengeList"").addClass(""is-invalid"");
                $(""#tbChallengeListFeedback"").addClass(""invalid-feedback"");
                $(""#tbChallengeListFeedback"").text(""Please do not leave this blank."");

                valid &= false;
            }
            else {
                valid &= true;
                $(""#tbChallengeList"").removeClass(""is-invalid"");
            }

            for (var row of studentRows)
            {
                console.log(""current row:"", row);
                console.log(""stud id row"", $(row).find('.tbStudentId'));
                var studentId = $(row).find('.tbStudentId').val();
                var studentName = $(row).find('.tbStudentName').val();

                console.log(""username/password: "", studentId, studentName);

                if (studentId === """" || studentName === """") {
                    $(""#tbStud");
            WriteLiteral(@"entListFeedback"").addClass(""d-block"");
                    $(""#tbStudentListFeedback"").addClass(""invalid-feedback"");
                    $(""#tbStudentListFeedback"").text(""Please do not leave any fields blank."");

                    valid &= false;
                }
                else {
                    valid &= true;
                    $(""#tbStudentListFeedback"").removeClass(""is-invalid"");
                    $(""#tbStudentListFeedback"").removeClass(""d-block"");

                    var studentObj = new StudentClass(studentId, studentName);
                    studentList.push(studentObj);
                }
            }

            if (studentList.length == 0)
            {
                $(""#tbStudentListFeedback"").addClass(""d-block"");
                $(""#tbStudentListFeedback"").addClass(""invalid-feedback"");
                $(""#tbStudentListFeedback"").text(""Please add at least one student."");

                valid &= false;
            }
            else {
                va");
            WriteLiteral(@"lid &= true;
                $(""#tbStudentListFeedback"").removeClass(""is-invalid"");
                $(""#tbStudentListFeedback"").removeClass(""d-block"");
            }

            return valid;
        }

        function SubmitForm() {
            if (ValidateForm()) {
                function WebFormData(code, challenges, studList) {
                    this.AccessCode = code;
                    this.ChallengeList = challenges;
                    this.StudentList = studList;
                }
                var webFormData = new WebFormData(accessCode, challengeList, studentList);

                var webFormDataInString = JSON.stringify(webFormData);

                //Sending the json to the /GameSession/Create API to add the game session into the database
                $.ajax({
                    url: ""/GameSession/create"",
                    type: ""POST"",
                    dataType: ""json"",
                    contentType: ""application/json"",
                    data: we");
            WriteLiteral(@"bFormDataInString,
                    success: function (response) {
                        if (response[""status""] == 404) {
                            $('#errorMsgAlertBox').removeClass('d-none');
                            $(""#errorMsgAlert"").text(response[""message""]);
                        }
                        else {
                            location.replace('/GameSession/Manage');
                        }
                    },
                    error: function (error) { console.log(error); }
                });
            }
        }
    });
</script>
");
        }
        #pragma warning restore 1998
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.ViewFeatures.IModelExpressionProvider ModelExpressionProvider { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IUrlHelper Url { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.IViewComponentHelper Component { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IJsonHelper Json { get; private set; }
        [global::Microsoft.AspNetCore.Mvc.Razor.Internal.RazorInjectAttribute]
        public global::Microsoft.AspNetCore.Mvc.Rendering.IHtmlHelper<dynamic> Html { get; private set; }
    }
}
#pragma warning restore 1591