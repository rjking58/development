using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;
    
namespace CustomControlsLib
{
    [DefaultProperty("Text")]
    [ToolboxData("<{0}:PalindromeCheckerRenderedControl runat=server></{0}:PalindromeCheckerRenderedControl>")]
    public class PalindromeCheckerRenderedControl : WebControl
    {
        public event EventHandler PalindromeFound;

        ArrayList alPalindromes = new ArrayList();

        [Bindable(true)]
        [Category("Appearance")]
        [DefaultValue("palindrome text goes here")]
        [Localizable(true)]
        public String Text
        {
            get
            {
                String s = (String)ViewState["Text"];
                return ((s == null) ? String.Empty : s);
            }

            set
            {
                ViewState["Text"] = value;

                alPalindromes = (ArrayList)this.ViewState["palindromes"];
                if (alPalindromes == null)
                {
                    alPalindromes = new ArrayList();
                }
                if (CheckForPalindrome())
                {
                    // make sure we have subscribers.. and if so
                    if (PalindromeFound != null)
                    {
                        // trigger the event.
                        PalindromeFound(this, EventArgs.Empty);
                    }
                    alPalindromes.Add(Text);
                }
                this.ViewState.Add("palindromes", alPalindromes);
            }
        }

        protected String StripNonAlphanumerics(string str)
        {
            String strStripped = (String)str.Clone();

            if (str != null)
            {
                char[] rgc = strStripped.ToCharArray();
                int i = 0;
                foreach (char c in rgc)
                {
                    if (char.IsLetterOrDigit(c))
                    {
                        i++;
                    }
                    else
                    {
                        strStripped = strStripped.Remove(i, 1);
                    }
                }
            }
            return strStripped;
        }

        protected bool CheckForPalindrome()
        {
            if (Text != null)
            {
                String strControlText = Text;
                String strTextToUpper = null;
                strTextToUpper = Text.ToUpper();

                strControlText =
                    StripNonAlphanumerics(strTextToUpper);
                char[] rgcReverse = strControlText.ToCharArray();
                Array.Reverse(rgcReverse);
                String strReverse = new String(rgcReverse);

                if (strControlText == strReverse)
                {
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }

        }

        protected void RenderPalindromesInTable(HtmlTextWriter output)
        {
            output.AddAttribute(HtmlTextWriterAttribute.Width, "50%");
            output.AddAttribute(HtmlTextWriterAttribute.Border, "1");
            output.RenderBeginTag(HtmlTextWriterTag.Table);
            foreach (string s in alPalindromes)
            {
                output.RenderBeginTag(HtmlTextWriterTag.Tr);
                output.AddAttribute(HtmlTextWriterAttribute.Align, "left");
                output.AddStyleAttribute(HtmlTextWriterStyle.FontSize, "medium");
                output.AddStyleAttribute(HtmlTextWriterStyle.Color, "blue");
                output.RenderBeginTag(HtmlTextWriterTag.Td);
                output.Write(s);
                output.RenderEndTag();
                output.RenderEndTag();
            }
            output.RenderEndTag();
        }
        protected override void RenderContents(HtmlTextWriter output)
        {
            if (CheckForPalindrome())
            {
                output.Write("this is a palindrome:");
                //output.Write("<br>");
                output.RenderBeginTag(HtmlTextWriterTag.Br);
                output.RenderEndTag();
                //output.Write("<FONT size=5 color=Blue>");
                output.RenderBeginTag(HtmlTextWriterTag.Font);
                output.AddStyleAttribute(HtmlTextWriterStyle.FontSize, "7");
                output.AddStyleAttribute(HtmlTextWriterStyle.Color, "blue");
                //output.Write("<B>");
                output.RenderBeginTag(HtmlTextWriterTag.B);
                output.Write(Text);
                //output.Write("</B>");
                output.RenderEndTag();
                //output.Write("</FONT>");
                output.RenderEndTag();
            }
            else
            {
                output.Write("this is NOT a palindrome:");
                //output.Write("<br>");
                output.RenderBeginTag(HtmlTextWriterTag.Br);
                output.RenderEndTag();
                //output.Write("<FONT size=5 color=Red>");
                output.RenderBeginTag(HtmlTextWriterTag.Font);
                output.AddStyleAttribute(HtmlTextWriterStyle.FontSize, "7");
                output.AddStyleAttribute(HtmlTextWriterStyle.Color, "red");
                //output.Write("<B>");
                output.RenderBeginTag(HtmlTextWriterTag.B);
                output.Write(Text);
                //output.Write("</B>");
                output.RenderEndTag();
                //output.Write("</FONT>");
                output.RenderEndTag();
            }
            output.RenderBeginTag(HtmlTextWriterTag.Br);
            output.RenderEndTag();
            RenderPalindromesInTable(output);
        }
    }
}
