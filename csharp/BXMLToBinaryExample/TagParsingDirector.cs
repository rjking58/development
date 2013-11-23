using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BXMLToBinaryExample
{
    class TagParsingDirector
    {
        BinaryFileContext ActivitiesFile            = new BinaryFileContext();
        BinaryFileContext ProfilesFile              = new BinaryFileContext();
        BinaryFileContext DevicesFile               = new BinaryFileContext();
        BinaryFileContext FavoritesFile             = new BinaryFileContext();
        BinaryFileContext SNSFile                   = new BinaryFileContext();
        BinaryFileContext MainFile                  = new BinaryFileContext();
        BinaryFileContext CurrentActiveFileContext  = null;

        public void SetActivitiesName(string name)
        {
            ActivitiesFile.Outputname = name;
        }
        public void SetProfilesName(string name)
        {
            ProfilesFile.Outputname = name;
        }
        public void SetDevicesName(string name)
        {
            DevicesFile.Outputname = name;
        }
        public void SetFavoritesName(string name)
        {
            FavoritesFile.Outputname = name;
        }
        public void SetSNSName(string name)
        {
            SNSFile.Outputname = name;
        }
        public void SetMainName(string name)
        {
            MainFile.Outputname = name;
        }
        public TagParsingDirector()
        {
            CurrentActiveFileContext = MainFile;
        }

        public void GenerateBinaryFiles()
        {
            ActivitiesFile.outputToBinary();
            ProfilesFile.outputToBinary();
            DevicesFile.outputToBinary();
            FavoritesFile.outputToBinary();
            SNSFile.outputToBinary();
            MainFile.outputToBinary();
        }
        public TagParsingContext GetParsingContext(string tagname,int linenumber)
        {
            TagParsingContext retVal = null;
            string lowcaseTagname = tagname.ToLower();
            switch(lowcaseTagname)
            {
                case TagNames.ACTIVITY:
                    retVal = new TagParsingContext_ACTIVITY(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.ACTIVITIES:
                    retVal = new TagParsingContext_ACTIVITIES(MainFile,linenumber);
                    CurrentActiveFileContext = ActivitiesFile;
                    break;
                case TagNames.BRAND:
                    retVal = new TagParsingContext_BRAND(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.CHANNELNUMBER:
                    retVal = new TagParsingContext_CHANNELNUMBER(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.DEVICES:
                    retVal = new TagParsingContext_DEVICES(MainFile,linenumber);
                    CurrentActiveFileContext = DevicesFile;
                    break;
                case TagNames.DEVICE:
                    retVal = new TagParsingContext_DEVICE(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.VOLUMEMASTER:
                    retVal = new TagParsingContext_VOLUMEMASTER(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.VOLUMELOCK:
                    retVal = new TagParsingContext_VOLUMELOCK(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.USERLOCK:
                    retVal = new TagParsingContext_USERLOCK(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.OEMLOCK:
                    retVal = new TagParsingContext_OEMLOCK(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.DEVICEID:
                    retVal = new TagParsingContext_DEVICEID(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.MODEL:
                    retVal = new TagParsingContext_MODEL(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.ICONREF:
                    retVal = new TagParsingContext_ICONREF(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.CODESET:
                    retVal = new TagParsingContext_CODESET(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.EXECUTOR:
                    retVal = new TagParsingContext_EXECUTOR(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.OBJCODE:
                    retVal = new TagParsingContext_OBJCODE(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.PREFIX:
                    retVal = new TagParsingContext_PREFIX(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.KEYMAP:
                    retVal = new TagParsingContext_KEYMAP(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.KEYID:
                    retVal = new TagParsingContext_KEYID(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.KEYFLAGS:
                    retVal = new TagParsingContext_KEYFLAGS(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.KEYIRCODES:
                    retVal = new TagParsingContext_KEYIRCODES(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.NAME8:
                    retVal = new TagParsingContext_NAME8(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.FAVORITES:
                    retVal = new TagParsingContext_FAVORITES(MainFile,linenumber);
                    CurrentActiveFileContext = FavoritesFile;
                    break;
                case TagNames.FAVORITE:
                    retVal = new TagParsingContext_FAVORITE(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.PROFILEINDEX:
                    retVal = new TagParsingContext_PROFILEINDEX(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.LEARNEDKEY:
                    retVal = new TagParsingContext_LEARNEDKEY(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.SYNTHESIZERKEY:
                    retVal = new TagParsingContext_SYNTHESIZERKEY(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.SYNTHESIZERCODE:
                    retVal = new TagParsingContext_SYNTHESIZERCODE(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.MACRO:
                    retVal = new TagParsingContext_MACRO(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.MACROPAIR:
                    retVal = new TagParsingContext_MACROPAIR(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.PUNCHTHRUMAP:
                    retVal = new TagParsingContext_PUNCHTHRUMAP(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.PUNCHTHRUSPEC:
                    retVal = new TagParsingContext_PUNCHTHRUSPEC(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.PROFILES:
                    retVal = new TagParsingContext_PROFILES(MainFile,linenumber);
                    CurrentActiveFileContext = ProfilesFile;
                    break;
                case TagNames.PROFILE:
                    retVal = new TagParsingContext_PROFILE(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.SNSTEST:
                    retVal = new TagParsingContext_SNSTEST(MainFile,linenumber);
                    CurrentActiveFileContext = SNSFile;
                    break;
                case TagNames.MOREDEVICES_TOTEST:
                    retVal = new TagParsingContext_MOREDEVICES_TOTEST(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.NEWDEVICE:
                    retVal = new TagParsingContext_NEWDEVICE(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.FAVORITEWIDTH:
                    retVal = new TagParsingContext_FAVORITEWIDTH(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.ENTERKEY:
                    retVal = new TagParsingContext_ENTERKEY(CurrentActiveFileContext,linenumber);
                    break;
                case TagNames.ROOT:
                    retVal = new TagParsingContext_ROOT(MainFile,linenumber);
                    break;
                case TagNames.HOME:
                    retVal = new TagParsingContext_HOME(MainFile,linenumber);
                    break;
                default:
                    retVal = null;
                    break;
            }
            return retVal;
        }
    }
}
