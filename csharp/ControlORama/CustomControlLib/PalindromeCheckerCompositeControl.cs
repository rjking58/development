using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Text;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace CustomControlLib
{
    [DefaultProperty("Text")]
    [ToolboxData("<{0}:PalindromeCheckerCompositeControl runat=server></{0}:PalindromeCheckerCompositeControl>")]
    public class PalindromeCheckerCompositeControl : CompositeControl
    {

        protected TextBox textboxPalindrome;
        protected Button buttonCheckForPalindrome;
        protected Label labelForTextBox;

        protected Table tablePalindromes;
        protected System.Collections.ArrayList alPalindromes;

        protected LiteralControl literalcontrolPalindromeStatus;

        public event EventHandler PalindromeFound;

        [Bindable(true)]
        [Category("Appearance")]
        [DefaultValue("PalindromeComposite")]
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
                this.alPalindromes = (System.Collections.ArrayList)this.ViewState["palindromes"];
                if (this.alPalindromes == null)
                {
                    this.alPalindromes = new System.Collections.ArrayList();
                }

                if (this.CheckForPalindrome())
                {
                    if (PalindromeFound != null)
                    {
                        PalindromeFound(this, EventArgs.Empty);
                    }
                    alPalindromes.Add(Text);
                    literalcontrolPalindromeStatus.Text =
                        "this is a palindrome <br> <FONT size=5 color=blue><B>"
                        + Text
                        + "</B> </FONT>";
                }
                else
                {
                    literalcontrolPalindromeStatus.Text =
                        "this is NOT a palindrome <br> <FONT size=5 color=red><B>"
                        + Text
                        + "</B> </FONT>";
                }
                this.ViewState.Add("palindromes", alPalindromes);
                this.BuildPalindromeTable();
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

        public void OnCheckPalindrome(Object o, System.EventArgs ea)
        {
            this.Text = this.textboxPalindrome.Text;
            this.CheckForPalindrome();
        }

        protected override void CreateChildControls()
        {
            labelForTextBox = new Label();
            labelForTextBox.Text = "Enter a Palindrome:";
            this.Controls.Add(labelForTextBox);

            textboxPalindrome = new TextBox();
            this.Controls.Add(textboxPalindrome);
            this.Controls.Add(new LiteralControl("<br/>"));

            buttonCheckForPalindrome = new Button();
            buttonCheckForPalindrome.Text = "Check For Palindrome";
            buttonCheckForPalindrome.Click += new EventHandler(OnCheckPalindrome);
            this.Controls.Add(buttonCheckForPalindrome);

            this.Controls.Add(new LiteralControl("<br/>"));

            literalcontrolPalindromeStatus = new LiteralControl();
            Controls.Add(literalcontrolPalindromeStatus);

            this.Controls.Add(new LiteralControl("<br/>"));

            this.tablePalindromes = new Table();
            this.Controls.Add(tablePalindromes);
        }

        protected void BuildPalindromeTable()
        {
            this.alPalindromes = (System.Collections.ArrayList)this.ViewState["palindromes"];
            if(this.alPalindromes != null)
            {
                foreach(string s in this.alPalindromes)
                {
                    TableCell tableCell = new TableCell();
                    tableCell.BorderStyle = BorderStyle.Double;
                    tableCell.BorderWidth = 3;
                    tableCell.Text = s;
                    TableRow tableRow = new TableRow();
                    tableRow.Cells.Add(tableCell);
                    this.tablePalindromes.Rows.Add(tableRow);
                }
            }
        }

    }
}
