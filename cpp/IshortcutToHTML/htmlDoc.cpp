class HTMLPStyle;
class HTMLParagraph;
class HTMLLine;

class HTMLDoc
{
public:
   GetText(**some file stream**);
   AddParagraph(HTMLParagraph *);
};

class HTMLParagraphStyle
{
public:
   virtual void GetText(**some file stream**) = 0;

};
class HTML_PS_LineHeight : public HTMLParagraphStyle
{
public:
   enum HeightSetting
   {
      normal,
      PT_1,
      PT_2
   };
   HTML_PS_LineHeight(HeightSetting Setting)
   : mSetting(Setting)
   {}
   virtual void GetText(**some file stream**);
   
private:
   HeightSetting mSetting;
};

class HTMLParagraph
{
public:
   GetText(**some file stream**);
   SetStyle(HTMLPStyle *);
   AddLine(HTMLLine *);
};

class HTMLTextStyle
{
   virtual void GetText(**some file stream**) = 0;

};

class HTML_TS_Strong : public HTMLTextStyle
{
   void GetText(**some file stream**);
};

class HTML_TS_Big : public HTMLTextStyle
{
   void GetText(**some file stream**);
};

class HTML_TS_URL : public HTMLTextStyle
{
   void GetText(**some file stream**);
   HTML_TS_URL(CString *URL);
};

class HTMLText
{
   virtual void GetText(**some file stream**) = 0;
};

class HTMLTab : public HTMLText
{
   virtual void GetText(**some file stream**);
};

class HTMLSimpleText : public HTMLText
{
   virtual void GetText(**some file stream**);
   void AddTextStyle(HTMLTextStyle *theStyle);
};


class HTMLLine
{
public:
   GetText(**some file stream**);
   AddURLText(CString * Text,
              CString * URL);
   Tab();
   AddText(CString *);
};
