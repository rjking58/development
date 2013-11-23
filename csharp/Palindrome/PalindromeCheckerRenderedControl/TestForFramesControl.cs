using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CustomControlsLib
{
    [DefaultProperty("Text")]
    [ToolboxData("<{0}:TestForFramesControl runat=server></{0}:TestForFramesControl>")]
    public class TestForFramesControl : WebControl
    {
        [Bindable(true)]
        [Category("Appearance")]
        [DefaultValue("Test For Frames")]
        [Localizable(true)]
        public string Text
        {
            get
            {
                String s = (String)ViewState["Text"];
                return ((s == null) ? String.Empty : s);
            }

            set
            {
                ViewState["Text"] = value;
            }
        }

        protected override void RenderContents(HtmlTextWriter output)
        {
            try
            {
                if (Page.Request.Browser.Frames)
                {
                    output.Write("This browser supports Frames");
                }
                else
                {
                    output.Write("This browser does NOT support Frames");
                }
            }
            catch (SystemException exc)
            {
                output.Write("exception:" + exc.Message);
            }

        }
    }
}
