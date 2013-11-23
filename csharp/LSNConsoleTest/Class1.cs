using System;
//using System.Drawing;
using System.Collections;
//using System.ComponentModel;
//using System.Windows.Forms;
using System.Data;
using System.Text;
using System.Text.RegularExpressions;
using System.Web;
using System.Net;
using System.IO;

namespace LSNConsoleTest
{
	// this is for testing.. 
	// will be replaced with dialog to gather info when needed.
	class httpTestDriver
	{
		public void run()
		{
			String your_usercode = "weezl";
			String your_password = "amemggjm";

            bool finished = false;
			bool post_mode = false;

			HttpWebRequest		wreq = null;
			HttpWebResponse 	wresp = null;
			StreamReader      	resp_stream_rdr = null;
			String            	html = null;
			HttpStatusCode		resp_stat_code;
			CookieCollection	resp_cookies = null;
			CookieCollection    cookies_to_write = null;

            // setup URI
            Uri					targetURI = new Uri("http://codo-linux1.bytemark.co.uk:8080/LSN/GameManager");
			Uri					oldURI;
			String				redirectLocation = "GameManager";
			int					currLoop = 0;
			while (		(!finished)
					&&	(currLoop++ < 10))
            {

				System.Console.WriteLine("==============================================");
				wreq =  (HttpWebRequest) WebRequest.Create(targetURI);
				wreq.CookieContainer = new CookieContainer();
				if (cookies_to_write != null)
				{
					wreq.CookieContainer.Add(cookies_to_write);
				}

                // start request..
				wreq.AllowAutoRedirect = false;
				if(post_mode)
				{
					string PostData = "playerName=" 
						+ HttpUtility.UrlEncode(your_usercode) 
						+ "&password=" 
						+ HttpUtility.UrlEncode(your_password);
					wreq.Method="POST";
					byte [] PostBuffer_ar = System.Text.Encoding.GetEncoding(1252).GetBytes(PostData);
					wreq.ContentLength = PostBuffer_ar.Length;

					Stream PostDataStream = wreq.GetRequestStream();
					PostDataStream.Write(PostBuffer_ar,0,PostBuffer_ar.Length);
					PostDataStream.Close();

					// make sure we don't do this again unless selected below :)
					post_mode = false;
				}

                // get response
				wresp = (HttpWebResponse) wreq.GetResponse();
				resp_stat_code = wresp.StatusCode;
				System.Console.WriteLine("Response:" + resp_stat_code.ToString());

                // cookies?  if so save off
				resp_cookies = wresp.Cookies;

				System.Console.WriteLine("Cookie Count:" + resp_cookies.Count.ToString());
				if (resp_cookies.Count > 0)
				{
					System.Console.WriteLine("getting cookies..");
					IEnumerator currCookie = resp_cookies.GetEnumerator();
					while(currCookie.MoveNext())
					{

						Cookie aCookie = (Cookie)currCookie.Current;
						System.Console.WriteLine("<><><><><START COOKIE><><><><>");
						System.Console.WriteLine("Expired:" + aCookie.Expired.ToString());
						System.Console.WriteLine("Expires:" + aCookie.Expires.ToString());
						System.Console.WriteLine("Discard:" + aCookie.Discard.ToString());
						System.Console.WriteLine("Domain:" + aCookie.Domain);
						System.Console.WriteLine("Path:" + aCookie.Path);
						System.Console.WriteLine(aCookie.ToString());
						System.Console.WriteLine("<><><><><END COOKIE><><><><>");
						if (aCookie.Expired != true)
						{
							System.Console.WriteLine("it is not expired.. woohoo!");
							if(cookies_to_write == null)
							{
								cookies_to_write = new CookieCollection();
							}
							aCookie.Path = "";
							cookies_to_write.Add(aCookie);
						}
						else
						{
							System.Console.WriteLine("it is expired.. :( !");
						}
					}
				}
				
				switch(resp_stat_code)
				{
					case HttpStatusCode.Found:
						// get the location
						redirectLocation = wresp.GetResponseHeader("Location");
						// setup new URI
						oldURI = targetURI;
						targetURI = new Uri(oldURI,redirectLocation,false);
						System.Console.WriteLine("redirectURI:" + targetURI.ToString());
						break;
					case HttpStatusCode.OK:
						resp_stream_rdr = new StreamReader(wresp.GetResponseStream());
						html = resp_stream_rdr.ReadToEnd();
						//System.Console.WriteLine(html);
						switch(redirectLocation)
						{
							case "login":
								System.Console.WriteLine("login page");
								// get all text after method=.. verify it says 'post'.
								// find <form method=? action="<redirectloc>">
								Regex formMethodRE = new Regex("<form +method=([a-zA-Z]+)[\t ]+action=\"(.+)\"");
								Match formMethodMatch = formMethodRE.Match(html);
								GroupCollection grps = formMethodMatch.Groups;
								System.Console.WriteLine("group count:" + grps.Count);
								if (grps.Count > 2)
								{
									// get first isolated match.. ([0] is the entire matched string)
									CaptureCollection captureCol  = grps[1].Captures;
									if(grps[1].Captures.Count > 0)
									{
										System.Console.WriteLine("returned form method:" + grps[1].Captures[0].Value);
										if (grps[1].Captures[0].Value.Equals("post"))
										{
											post_mode = true;
											// location was found.. get it..
											System.Console.WriteLine("the form action is:" + grps[2].Captures[0].Value);

											redirectLocation = grps[2].Captures[0].Value;
											oldURI = targetURI;
											targetURI = new Uri(oldURI,redirectLocation,false);
											System.Console.WriteLine("redirectURI:" + targetURI.ToString());
											// verify fields for post..
											Regex playernameRE = new Regex("<input.+type=.+name=\"playerName\"");
											Match playernameMatch = formMethodRE.Match(html);
											Regex passwordRE = new Regex("<input.+type=.+name=\"password\"");
											Match passwordMatch = formMethodRE.Match(html);
											if (	(!passwordMatch.Success)
												||	(!playernameMatch.Success))
											{
												//todo:: error.. stop and report.
												System.Console.WriteLine("playername or password fields have changed.. ERROR");
												finished = true;
											}
											// populate with username/password
										}
										else
										{
											//todo:: not post mode!! report and die.
											System.Console.WriteLine("did not find 'post' on 'login' page.. ERROR");
											finished = true;
										}
									}
									else
									{
										//todo:: didn't find proper fields.. report and die.
										System.Console.WriteLine("<form ..> not found on login page... ERROR"); 
										finished = true;
									}
									// now get UserCode/Password field names and prompting so that we
									// can setup the input dialog correctly.

								}
								else
								{
									// post not found.. OOPS
									System.Console.WriteLine("<form ..> not found on login page... ERROR"); 
									finished = true;
									// todo:: error condition..report accordingly
								}
								break;
							case "GameManager":
								System.Console.WriteLine("GameManager page");
								finished = true;
                                findPlayGameEntries(html);
								break;
							case "GameManager?newRecruit=none":
								System.Console.WriteLine("GameManager?newRecruit=none page");
								finished = true;
                                findPlayGameEntries(html);
                                break;
							default:
								break;
						}
						break;
					default :
						System.Console.WriteLine("uh-oh, bad news now!!");
						finished = true;
						//todo:: report bad page returned..
						break;
				}

                //type (redirect [302/Found], [200/OK] ?
                //  302----------------
                //      get location and setup new URI for us to go to.. (based on old URI)
                //  200----------------
                //      if html is on "login" page.. (<form method=post action="LoginCheck">
                //          pick up <input ... name="playerName" ..>
                //                  <input ... name="password" ..>
                //      else
                //          html is end page.. "woohoo"!

				wresp.Close();


            }
		}

//<tr class="tableroweven">
//    <td class="tabletext">138528</td>
//    <td class="tabletext">BARTOK              </td>
//    <td class="tabletext">Titan Spaceport               </td>
//    <td class="tabletext">-                   </td>
//    <td class="tabletext">L</td>
//    <td class="tabletext">26:21</td>
//    <td class="tabletext">23/30</td>
//    <td class="tabletext">
//        <a href="Game?game_id=138528;player_num=2;tstatus=turn;p_rating=1010;admin_id=0">PLAY TURN</a>
//        </td>
//</tr>
        private void findPlayGameEntries(String html)
        {
            System.Console.WriteLine("findPlayGameEntries ENTRY");
            //System.Console.WriteLine(html);
//            Regex PlayTurnRE = new Regex("<tr.*\">.*<td.*\">(.*)</td>.*<a href.*\">(PLAY TURN)</a>",RegexOptions.Singleline); // 
            //Regex PlayTurnRE = new Regex("<tr class.*\">.*<td class.*\">(.*)</td>.*<td class.*\">(.*)</td>.*<td class.*\">(.*)</td>.*<td class.*\">(.*)</td>.*<td class.*\">(.*)</td>.*<td class.*\">(.*)</td>.*<td class.*\">(.*)</td>.*<a href(.*)\">(PLAY TURN)</a>",RegexOptions.Singleline);
              Regex PlayTurnRE = new Regex("(<td class.*\">(.*)</td>.*)+<a href(.*)\">(PLAY TURN)</a>",RegexOptions.Singleline);
//            Regex PlayTurnRE = new Regex("<a.*\">(.*)</a>");
            MatchCollection PlayTurnMatches = PlayTurnRE.Matches(html);
            IEnumerator matchEnumerator = PlayTurnMatches.GetEnumerator();
            while(matchEnumerator.MoveNext())
            {
                GroupCollection grpColl = ((Match) matchEnumerator.Current).Groups;
                IEnumerator grpEnumerator = grpColl.GetEnumerator();
                while(grpEnumerator.MoveNext())
                {
                    IEnumerator captureEnum = ((Group)grpEnumerator.Current).Captures.GetEnumerator();
                    while(captureEnum.MoveNext())
                    {   
                        System.Console.WriteLine("Capture+_+_+_" + ((Capture)(captureEnum.Current)).Value + "_+_+_+");
                    }
                }
            }
            System.Console.WriteLine("findPlayGameEntries EXIT");
        }
	}

	/// <summary>
	/// Summary description for Class1.
	/// </summary>
	class Class1
	{
		/// <summary>
		/// The main entry point for the application.
		/// </summary>
		[STAThread]
		static void Main(string[] args)
		{
			//
			// TODO: Add code to start application here
			//
            httpTestDriver reqDriver = new httpTestDriver();
            reqDriver.run();
		}
	}
}
/*  future looking.. a design take if things keep lookign =
class cookiePersister
{
    private int tmp; // just for now so things work ok.
}

abstract class httpServicePostAction
{   
    public abstract void doAction(HttpWebRequest wreq);
}

class httpServiceLoginCheckPost : httpServicePostAction
{
    public override void doAction(HttpWebRequest wreq)
    {
        string PostData = "playerName=" 
            + HttpUtility.UrlEncode("weezl") 
            + "&password=" 
            + HttpUtility.UrlEncode("amemggjm");
        wreq.Method="POST";
        byte [] PostBuffer_ar = System.Text.Encoding.GetEncoding(1252).GetBytes(PostData);
        wreq.ContentLength = PostBuffer_ar.Length;

        Stream PostDataStream = wreq.GetRequestStream();
        PostDataStream.Write(PostBuffer_ar,0,PostBuffer_ar.Length);
        PostDataStream.Close();
    }
}

abstract class httpServiceAction
{
    String  mActionURI;
    bool    mDefault;
    String  redirectLocation;
    public httpServiceAction(String actionURI,
        bool   isDefault)
    {
        mActionURI = actionURI;
        mDefault = isDefault;
    }

    bool Equals(String testAction)
    {
        return testAction.Equals(mActionURI);
    }

    bool isDefault()
    {
        return mDefault;
    }


    public abstract void doAction(  httpServices services,
        httpServicePostAction anAction); // have to pass in something.. not determined yet..
}

abstract class httpServiceOKAction : httpServiceAction
{
    public httpServiceOKAction(String   actionURI,
        bool     isDefault) : base(actionURI,isDefault)
    {
    }
}

abstract class httpServiceFoundAction : httpServiceAction
{
    public httpServiceFoundAction(String    actionURI,
        bool      isDefault) : base(actionURI,isDefault)
    {
    }
}



class httpServices
{

    private Uri                     mTargetURI;
    private Uri                     mOldURI;
    private cookiePersister         mCookiePersist;
    private bool                    mDefaultOKActionfound = false;
    private bool                    mDefaultFoundActionfound = false;
        
    private httpServicePostAction   mPostAction  = null;
    //        StreamReader      	    resp_stream_rdr = null;
    //        String            	    html = null;



    public httpServices(Uri StartURI, cookiePersister cookpersist)
    {
        mTargetURI = StartURI;
        mOldURI = null;
        mCookiePersist = cookpersist;
    }

    private Uri redirectToNewURI(String redirectLoc)
    {
        mOldURI = mTargetURI;
        mTargetURI = new Uri(mOldURI,redirectLoc,false);
        return mTargetURI;
    }
    public void setPostAction(httpServicePostAction postAction)
    {
        mPostAction = postAction;
    }

    public bool addFoundAction(httpServiceFoundAction fa)
    {
        bool retVal = false; // false = BAD
        if (fa.isDefault() && mDefaultFoundActionfound)
        {
            System.Console.WriteLine("more than one FoundAction being added.. bad bad.");
        }
        else
        {

        }
    }
    public bool addOKAction(httpServiceOKAction)
    {
    }
    public void Run()
    {

        bool                finished = false;
        bool                post_mode = false;
        CookieCollection    cookies_to_write = null;            
        HttpWebRequest		wreq = null;
        HttpWebResponse 	wresp = null;
        HttpStatusCode		resp_stat_code;
        CookieCollection	resp_cookies = null;
        String              redirectLocation = "";

        // setup URI
        while (!finished)
        {
            System.Console.WriteLine("==============================================");
            wreq =  (HttpWebRequest) WebRequest.Create(mTargetURI);
            wreq.CookieContainer = new CookieContainer();
            if (cookies_to_write != null)
            {
                wreq.CookieContainer.Add(cookies_to_write);
            }

            // start request..
            wreq.AllowAutoRedirect = false;
            if(post_mode)
            {
                mPostAction.doAction(wreq);                    
                // make sure we don't do this again unless selected below :)
                post_mode = false;
            }

            // get response
            wresp = (HttpWebResponse) wreq.GetResponse();
            resp_stat_code = wresp.StatusCode;
            System.Console.WriteLine("Response:" + resp_stat_code.ToString());

            // cookies?  if so save off
            resp_cookies = wresp.Cookies;

            System.Console.WriteLine("Cookie Count:" + resp_cookies.Count.ToString());
            if (resp_cookies.Count > 0)
            {
                System.Console.WriteLine("getting cookies..");
                IEnumerator currCookie = resp_cookies.GetEnumerator();
                while(currCookie.MoveNext())
                {

                    Cookie aCookie = (Cookie)currCookie.Current;
                    System.Console.WriteLine("<><><><><START COOKIE><><><><>");
                    System.Console.WriteLine("Expired:" + aCookie.Expired.ToString());
                    System.Console.WriteLine("Expires:" + aCookie.Expires.ToString());
                    System.Console.WriteLine("Discard:" + aCookie.Discard.ToString());
                    System.Console.WriteLine("Domain:" + aCookie.Domain);
                    System.Console.WriteLine("Path:" + aCookie.Path);
                    System.Console.WriteLine(aCookie.ToString());
                    System.Console.WriteLine("<><><><><END COOKIE><><><><>");
                    if (aCookie.Expired != true)
                    {
                        System.Console.WriteLine("it is not expired.. woohoo!");
                        if(cookies_to_write == null)
                        {
                            cookies_to_write = new CookieCollection();
                        }
                        aCookie.Path = "";
                        cookies_to_write.Add(aCookie);
                    }
                    else
                    {
                        System.Console.WriteLine("it is expired.. :( !");
                    }
                }
            }
				
            switch(resp_stat_code)
            {
                case HttpStatusCode.Found:
                    // get the location
                    redirectLocation = wresp.GetResponseHeader("Location");
                    // setup new URI
                    oldURI = targetURI;
                    targetURI = new Uri(oldURI,redirectLocation,false);
                    System.Console.WriteLine("redirectURI:" + targetURI.ToString());
                    break;
                case HttpStatusCode.OK:
                    bool post_found = false;
                    resp_stream_rdr = new StreamReader(wresp.GetResponseStream());
                    html = resp_stream_rdr.ReadToEnd();
                    System.Console.WriteLine(html);
                switch(redirectLocation)
                {
                    case "login":
                        System.Console.WriteLine("login page");
                        // get all text after method=.. verify it says 'post'.
                        // find <form method=? action="<redirectloc>">
                        Regex formMethodRE = new Regex("<form +method=([a-zA-Z]+)[\t ]+action=\"(.+)\"");
                        Match formMethodMatch = formMethodRE.Match(html);
                        GroupCollection grps = formMethodMatch.Groups;
                        System.Console.WriteLine("group count:" + grps.Count);
                        if (grps.Count > 2)
                        {
                            // get first isolated match.. ([0] is the entire matched string)
                            CaptureCollection captureCol  = grps[1].Captures;
                            if(grps[1].Captures.Count > 0)
                            {
                                System.Console.WriteLine("returned form method:" + grps[1].Captures[0].Value);
                                if (grps[1].Captures[0].Value.Equals("post"))
                                {
                                    post_mode = true;
                                    // location was found.. get it..
                                    System.Console.WriteLine("the form action is:" + grps[2].Captures[0].Value);

                                    redirectLocation = grps[2].Captures[0].Value;
                                    oldURI = targetURI;
                                    targetURI = new Uri(oldURI,redirectLocation,false);
                                    System.Console.WriteLine("redirectURI:" + targetURI.ToString());
                                    // verify fields for post..
                                    Regex playernameRE = new Regex("<input.+type=.+name=\"playerName\"");
                                    Match playernameMatch = formMethodRE.Match(html);
                                    Regex passwordRE = new Regex("<input.+type=.+name=\"password\"");
                                    Match passwordMatch = formMethodRE.Match(html);
                                    if (	(!passwordMatch.Success)
                                        ||	(!playernameMatch.Success))
                                    {
                                        //todo:: error.. stop and report.
                                        System.Console.WriteLine("playername or password fields have changed.. ERROR");
                                        finished = true;
                                    }
                                    // populate with username/password
                                }
                                else
                                {
                                    //todo:: not post mode!! report and die.
                                    System.Console.WriteLine("did not find 'post' on 'login' page.. ERROR");
                                    finished = true;
                                }
                            }
                            else
                            {
                                //todo:: didn't find proper fields.. report and die.
                                System.Console.WriteLine("<form ..> not found on login page... ERROR"); 
                                finished = true;
                            }
                            // now get UserCode/Password field names and prompting so that we
                            // can setup the input dialog correctly.

                        }
                        else
                        {
                            // post not found.. OOPS
                            System.Console.WriteLine("<form ..> not found on login page... ERROR"); 
                            finished = true;
                            // todo:: error condition..report accordingly
                        }
                        break;
                    case "GameManager":
                        System.Console.WriteLine("GameManager page");
                        finished = true;
                        break;
                    case "GameManager?newRecruit=none":
                        System.Console.WriteLine("GameManager?newRecruit=none page");
                        finished = true;
                        break;
                    default:
                        break;
                }
                    break;
                default :
                    System.Console.WriteLine("uh-oh, bad news now!!");
                    finished = true;
                    //todo:: report bad page returned..
                    break;
            }

            //type (redirect [302/Found], [200/OK] ?
            //  302----------------
            //      get location and setup new URI for us to go to.. (based on old URI)
            //  200----------------
            //      if html is on "login" page.. (<form method=post action="LoginCheck">
            //          pick up <input ... name="playerName" ..>
            //                  <input ... name="password" ..>
            //      else
            //          html is end page.. "woohoo"!

            wresp.Close();


        }
    }
}



class httpReqDriver
{
    public void run()
    {

    }
}

*/