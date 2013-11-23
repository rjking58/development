#define TRACE_EMIT

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;
using System.Globalization;

namespace BXMLToBinaryExample
{


    class GeneralParsingException : ApplicationException
    {
        public GeneralParsingException() 
        {
        }
        public GeneralParsingException(string message) 
        : base (message)
        {
        }
    }
    class MissingParameter : ApplicationException
    {
        public MissingParameter() 
        {
        }
        public MissingParameter(string message) 
        : base (message)
        {
        }
    }
 

    class Program
    {
    
        enum CommandLineStates 
        {
            GARBAGE,
            INPUTFILENAME_FLAG,
            INPUTFILENAME_TEXT,
            OUTPUTFILENAME_FLAG,
            OUTPUTFILENAME_TEXT
        }

        static void Main(string[] args)
        {
        
            
            string inputFname = "";
            string outputFname = "";
            
            // command line arguments..        
            Console.WriteLine("Number of command line parameters = {0}",
                              args.Length);
            // -i <input filename>
            // -o <output filename>
            // -h help.
            
            CommandLineStates cl_state = CommandLineStates.GARBAGE;
            
            for(int i = 0; i < args.Length; i++)
            {
                Console.WriteLine("Arg[{0}] = [{1}]", i, args[i]);
                if(args[i] == "-i")
                {
                    cl_state = CommandLineStates.INPUTFILENAME_FLAG;
                }
                if(args[i] == "-o")
                {
                    cl_state = CommandLineStates.OUTPUTFILENAME_FLAG;
                }
                if(args[i] == "-h")
                {
                    Console.WriteLine(" -h                  : help");
                    Console.WriteLine(" -i <inputfilename>  : file name to use as input");
                    Console.WriteLine(" -o <outputfilename> : file name to use as output");
                    break;
                }
                switch(cl_state)
                {
                    default:
                    case CommandLineStates.GARBAGE:
                        break;
                    case CommandLineStates.INPUTFILENAME_FLAG:
                        cl_state = CommandLineStates.INPUTFILENAME_TEXT;
                        break;
                    case CommandLineStates.INPUTFILENAME_TEXT:
                        inputFname = args[i];
                        cl_state = CommandLineStates.GARBAGE;
                        break;
                    case CommandLineStates.OUTPUTFILENAME_FLAG:
                        cl_state = CommandLineStates.OUTPUTFILENAME_TEXT;
                        break;
                    case CommandLineStates.OUTPUTFILENAME_TEXT:
                        outputFname = args[i];
                        cl_state = CommandLineStates.GARBAGE;
                        break;
                }
            }
            
            Console.WriteLine(String.Format("input[{0}] output[{1}]",inputFname,outputFname));
            if( ! File.Exists(inputFname))
            {
                Console.WriteLine(String.Format("file does not exist: [{0}]",inputFname));
            }
            else if (outputFname == "")
            {
                Console.WriteLine("must provide output filename!");
            }
            else
            {
        
                TagParsingDirector tagDirector = new TagParsingDirector();
                tagDirector.SetMainName(outputFname);
                
                XmlTextReader xr = new XmlTextReader(inputFname);
    
                TagParsingContext           currentContext = null;
                Stack<TagParsingContext>    contextStack = new Stack<TagParsingContext>();
                
                while(!xr.EOF)
                {
                    
                    xr.Read();
                    if(xr.NodeType == XmlNodeType.Element)
                    {
                        if(currentContext == null)
                        {
                            currentContext = tagDirector.GetParsingContext(xr.Name,xr.LineNumber);
                            if(currentContext == null)
                            {
                                Console.WriteLine(String.Format("ERROR:  Line[{0}]",xr.LineNumber));
                                Console.WriteLine(String.Format("unrecognized tag [{0}]",xr.Name));
                                break;
                            }
                        }
                        else
                        {
                            if(currentContext.IsLegal(xr.Name))
                            {
                                // emit if needed.
                                currentContext.emit();
                                contextStack.Push(currentContext);
                                //Console.WriteLine(xr.Name);
                                currentContext = tagDirector.GetParsingContext(xr.Name,xr.LineNumber);
                                if(currentContext == null)
                                {
                                    Console.WriteLine(String.Format("ERROR:  Line[{0}]",xr.LineNumber));
                                    Console.WriteLine(String.Format("unrecognized tag [{0}]",xr.Name));
                                    break;
                                }
                            }
                            else
                            {
                                Console.WriteLine(String.Format("ERROR:  Line[{0}]",xr.LineNumber));
                                Console.WriteLine(String.Format("illegal child tag [{0}] for tag [{1}]",xr.Name,currentContext.tagName()));
                                break;
                            }
                        }
                        currentContext.AddTagNameToFileContext();
                    }
                    else if(xr.NodeType == XmlNodeType.EndElement)
                    {
                        string lowerCaseTag = xr.Name.ToLower();
                        if(currentContext.tagName() != lowerCaseTag)
                        {
                            Console.WriteLine(String.Format("ERROR:  Line[{0}]",xr.LineNumber));
                            Console.WriteLine("bad closing tag");
                            Console.WriteLine(String.Format("expected [{0}]   actual [{1}]",currentContext.tagName(),xr.Name));
                        }

                        if( ! currentContext.closeElementAction())
                        {
                            break;
                        }

                        if(contextStack.Count == 0)
                        {
                            currentContext = null;
                        }
                        else
                        {
                            currentContext = contextStack.Pop();
                        }
                    }
                    else if(xr.NodeType == XmlNodeType.Text)
                    {
                        if(currentContext == null)
                        {
                            Console.WriteLine(String.Format("ERROR:  Line[{0}]",xr.LineNumber));
                            Console.WriteLine("text appears without an enclosing element tag!!");
                            break;
                        }
                        try
                        {
                            //Console.WriteLine(String.Format("---[{0}]---",xr.Value));
                            currentContext.parseValue(xr.Value);
                            currentContext.setOutputName(tagDirector);
                        }
                        catch(GeneralParsingException)
                        {
                            Console.WriteLine(String.Format("ERROR:  Line[{0}]",xr.LineNumber));
                            break;
                        }
                        currentContext.emit();
                    }
                }

                tagDirector.GenerateBinaryFiles();
            }
        }        
    }
}

