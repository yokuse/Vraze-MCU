#pragma checksum "C:\Users\rcwww\Desktop\Y2T1\2104\Project\ict2104_carProj\2101WebPortal\2101WebPortal\Views\Challenge\Create.cshtml" "{ff1816ec-aa5e-4d10-87f7-6f4963833460}" "281c4a75bc9e0dfc350aaa2f255d77a88b8c07a7"
// <auto-generated/>
#pragma warning disable 1591
[assembly: global::Microsoft.AspNetCore.Razor.Hosting.RazorCompiledItemAttribute(typeof(AspNetCore.Views_Challenge_Create), @"mvc.1.0.view", @"/Views/Challenge/Create.cshtml")]
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
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"281c4a75bc9e0dfc350aaa2f255d77a88b8c07a7", @"/Views/Challenge/Create.cshtml")]
    [global::Microsoft.AspNetCore.Razor.Hosting.RazorSourceChecksumAttribute(@"SHA1", @"d74cd0e45e0e484cb5131bc43133c1eb3e8ce708", @"/Views/_ViewImports.cshtml")]
    public class Views_Challenge_Create : global::Microsoft.AspNetCore.Mvc.Razor.RazorPage<dynamic>
    {
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_0 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "Admin", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_1 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-action", "Home", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
        private static readonly global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute __tagHelperAttribute_2 = new global::Microsoft.AspNetCore.Razor.TagHelpers.TagHelperAttribute("asp-controller", "Challenge", global::Microsoft.AspNetCore.Razor.TagHelpers.HtmlAttributeValueStyle.DoubleQuotes);
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
#line 1 "C:\Users\rcwww\Desktop\Y2T1\2104\Project\ict2104_carProj\2101WebPortal\2101WebPortal\Views\Challenge\Create.cshtml"
  
    ViewData["Title"] = "Create New Challenge";

#line default
#line hidden
#nullable disable
            WriteLiteral(@"<div class=""text-center"">
    <h1 class=""display-4"">Add New Challenge</h1>
</div>
<div class=""row"">
    <div class=""col-md-12"">
        <h6>
            <nav aria-label=""breadcrumb"">
                <ol class=""breadcrumb"">
                    <li class=""breadcrumb-item"">");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "281c4a75bc9e0dfc350aaa2f255d77a88b8c07a76205", async() => {
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
            WriteLiteral("</li>\n                    <li class=\"breadcrumb-item\">");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "281c4a75bc9e0dfc350aaa2f255d77a88b8c07a77617", async() => {
                WriteLiteral("Challenges");
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
                    <li class=""breadcrumb-item active"" aria-current=""page"">Create New Challenge</li>
                </ol>
            </nav>
        </h6>
    </div>
</div>
<div class=""col-lg-8 mx-auto mt-3"">
    <div class=""card"">
        <div class=""card-body"">
            <h2 class=""text-info"">Challenge Information</h2>
            ");
            __tagHelperExecutionContext = __tagHelperScopeManager.Begin("form", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "281c4a75bc9e0dfc350aaa2f255d77a88b8c07a79335", async() => {
                WriteLiteral(@"
                <div class=""form-group row"">
                    <label for=""tbImage"" class=""col-sm-2 col-form-label"">Map Image</label>
                    <div class=""col-sm-10"">
                        <div class=""custom-file"">
                            <input type=""file"" class=""custom-file-input"" id=""tbImage"">
                            <label id=""lblFile"" class=""custom-file-label"" for=""customFile"">Choose file</label>
                        </div>
                    </div>
                </div>
                <div class=""form-group row"">
                    <label class=""col-sm-2 col-form-label"">Hints</label>
                    <div class=""col-sm-10"">
                        <input type=""text"" class=""form-control mb-2"" placeholder=""Hint #1"" id=""tbHint1"" />
                        <input type=""text"" class=""form-control mb-2"" placeholder=""Hint #2"" id=""tbHint2"" />
                        <input type=""text"" class=""form-control mb-2"" placeholder=""Hint #3"" id=""tbHint3"" />
                    </div>
    ");
                WriteLiteral(@"            </div>
                <div class=""form-group row"">
                    <label for=""tbSolution"" class=""col-sm-2 col-form-label"">Solution</label>
                    <div class=""col-sm-10"">
                        <input type=""text"" class=""form-control"" id=""tbSolution"">
                    </div>
                </div>
                <div class=""form-group form-check"">
                    <input type=""checkbox"" class=""form-check-input"" id=""cbTutorial"">
                    <label for=""cbTutorial"" class=""form-check-label"">Is tutorial Challenge?</label>
                </div>
                <div class=""form-group row"">
                    <div class=""col-md-6"">
                        ");
                __tagHelperExecutionContext = __tagHelperScopeManager.Begin("a", global::Microsoft.AspNetCore.Razor.TagHelpers.TagMode.StartTagAndEndTag, "281c4a75bc9e0dfc350aaa2f255d77a88b8c07a711436", async() => {
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
                WriteLiteral("\n                    </div>\n                    <div class=\"col-md-6\">\n                        <span id=\"btnSubmit\" class=\"btn btn-primary btn-block\">Create</span>\n                    </div>\n                </div>\n            ");
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

<script>var CLOUDINARY_URL = ""https://api.cloudinary.com/v1_1/dj6afbyih/image/upload"";
    var CLOUDINARY_UPLOAD_PRESET = ""gsdndegy"";
    var currentFile = null;
    $(document).ready(function () {

        $(""#tbImage"").on(""change"", function (event) {
            currentFile = event.target.files[0];
            $(""#lblFile"").text($('input[type=file]').val().split('\\').pop());
        });

        $(""#btnSubmit"").click(function () {
            uploadToCloudinaryAndSubmit();
        });

        function submitForm(imageUri) {
            var hints = [];
            hints.push($(""#tbHint1"").val());
            hints.push($(""#tbHint2"").val());
            hints.push($(""#tbHint3"").val());

            function WebFormData(hints, imageUri, solution, istut) {
                this.Hints = hints;
                this.MapImageUrl = imageUri;
                this.Solution = solution;
                this.IsTutorialChallenge = istut;
                this.IsDeleted = false
          ");
            WriteLiteral(@"  }
            var webFormData = new WebFormData(hints, imageUri, $(""#tbSolution"").val(), $('#cbTutorial').is("":checked""));

            var webFormDataInString = JSON.stringify(webFormData);

            console.log(webFormData);
            console.log(webFormDataInString);

            $.ajax({
                url: ""/challenge/create"",
                type: ""POST"",
                dataType: ""json"",
                contentType: ""application/json"",
                data: webFormDataInString,
                success: function (response) {
                    location.replace('/Challenge/Manage');
                },
                error: function (error) { console.log(error); }
            });
        }

        function uploadToCloudinaryAndSubmit() {
            var formData = new FormData();
            formData.append(""file"", currentFile);
            formData.append(""upload_preset"", CLOUDINARY_UPLOAD_PRESET);

            $.ajax({
                url: CLOUDINARY_URL,
                type: ""POST"",
       ");
            WriteLiteral(@"         contentType: false,
                processData: false,
                data: formData,
                success: function (response) {
                    var imageUri = response[""url""]; //Link of the uploaded image

                    submitForm(imageUri)
                },
                error: function (error) {
                    console.log(error);
                },
            });
        }
    });</script>");
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