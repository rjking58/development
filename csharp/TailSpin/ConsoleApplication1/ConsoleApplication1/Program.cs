
using Microsoft.VisualBasic;
using System;
using System.Collections;
using System.Collections.Generic;
using System.Data;
using System.Diagnostics;

using SmallBasic;

static class Tetris1Module
{
	static int moveDirection;
    static int BOXES;
    static int BWIDTH;
    static int XOFFSET;
    static int YOFFSET;
    static int CWIDTH;
	static int CHEIGHT;
	static int STARTDELAY;
	static int ENDDELAY;
	static int PREVIEW_xpos;
	static int PREVIEW_ypos;
	static int template;
	static int nextPiece;
	static int h;
	static int __end;
	static int sessionDelay;
	static int delay;
	static int thisPiece;
	static int ypos;
	static int done;
	static int xpos;
	static int yposdelta;
	static int delayIndex;
	static int invalidMove;
	static int basetemplate;
	static int rotation;
	static int xposbk;
	static int XOFFSETBK;
	static int YOFFSETBK;
	static int L;
	static int i;
	static int v;
	static int x;
	static int y;
	static int hcount;
	static int s;
	static int score;
	static int linesCleared;
	static int piece;
	static int x1;
    static int y1;
	public static void Main()
	{
		GraphicsWindow.KeyDown += HandleKey;
		GraphicsWindow.BackgroundColor = GraphicsWindow.GetColorFromRGB(253, 252, 251);

		while (true) {
			BOXES = 4;
			// number of boxes per piece
			BWIDTH = 25;
			// box width in pixels
			XOFFSET = 40;
			// Screen X offset in pixels of where the board starts
			YOFFSET = 40;
			// Screen Y offset in pixels of where the board starts
			CWIDTH = 10;
			// Canvas Width, in number of boxes
			CHEIGHT = 20;
			// Canvas Height, in number of boxes.
			STARTDELAY = 800;
			ENDDELAY = 175;
			PRVIEW_xpos = 13;
			PREVIEW_ypos = 2;

			GraphicsWindow.Clear();
			GraphicsWindow.Title = "Small Basic Tetris";
			GraphicsWindow.Height = 580;
			GraphicsWindow.Width = 700;
			GraphicsWindow.Show();

			SetupTemplates();
			SetupCanvas();
			MainLoop();

			GraphicsWindow.ShowMessage("Game Over", "Small Basic Tetris");
		}





		// creates template that's a rotated basetemplate













	}
	public static void MainLoop()
	{
		template = System.Text.Append("template", Microsoft.SmallBasic.Library.Math.GetRandomNumber(7));

		CreatePiece();
		// in: template ret: h
		nextPiece = h;

		__end = 0;
		sessionDelay = STARTDELAY;
		while (__end == 0) {
			if (sessionDelay > ENDDELAY) {
				sessionDelay = sessionDelay - 1;
			}

			delay = sessionDelay;
			thisPiece = nextPiece;
			template = System.Text.Append("template", Microsoft.SmallBasic.Library.Math.GetRandomNumber(7));

			CreatePiece();
			// in: template ret: h
			nextPiece = h;
			DrawPreviewPiece();

			h = thisPiece;

			ypos = 0;
			done = 0;
			xpos = 3;
			// always drop from column 3
			CheckStop();
			// in: ypos, xpos, h ret: done
			if (done == 1) {
				ypos = ypos - 1;
				MovePiece();
				//in: ypos, xpos, h
				__end = 1;
			}

			yposdelta = 0;
			while ((done == 0) | (yposdelta > 0)) {
				MovePiece();
				//in: ypos, xpos, h

				// Delay, but break if the delay get set to 0 if the piece gets dropped
				delayIndex = delay;
				while ((delayIndex > 0) & (delay > 0)) {
					Program.Delay(10);
					delayIndex = delayIndex - 10;
				}

				if (yposdelta > 0) {
					yposdelta = yposdelta - 1;
					// used to create freespin, when the piece is rotated
				} else {
					ypos = ypos + 1;
					// otherwise, move the piece down.
				}

				// Check if the piece should stop.
				CheckStop();
				// in: ypos, xpos, h ret: done
			}
		}
	}
	public static void HandleKey()
	{
		// Stop game
		if (GraphicsWindow.LastKey == (Primitive)"Escape") {
			Program.End();
		}

		// Move piece left
		if (GraphicsWindow.LastKey == (Primitive)"Left") {
			moveDirection = -1;
			ValidateMove();
			// in: ypos, xpos, h, moveDirection ret: invalidMove = 1 or -1 or 2 if move is invalid, otherwise 0
			if (invalidMove == 0) {
				xpos = xpos + moveDirection;
			}
			MovePiece();
			//in: ypos, xpos, h
		}

		// Move piece right
		if (GraphicsWindow.LastKey == (Primitive)"Right") {
			moveDirection = 1;
			ValidateMove();
			// in: ypos, xpos, h, moveDirection ret: invalidMove = 1 or -1 or 2 if move is invalid, otherwise 0
			if (invalidMove == 0) {
				xpos = xpos + moveDirection;
			}
			MovePiece();
			//in: ypos, xpos, h
		}

		// Move piece down
		if ((GraphicsWindow.LastKey == (Primitive)"Down") | (GraphicsWindow.LastKey == (Primitive)"Space")) {
			delay = 0;
		}

		// Rotate piece
		if (GraphicsWindow.LastKey == (Primitive)"Up") {
			basetemplate = Microsoft.SmallBasic.Library.Array.GetValue(h, -1);
			// Array.GetValue(h, -1) = the template name
			template = "temptemplate";
			rotation = "CW";
			CopyPiece();
			//in basetemplate, template, rotation

			Microsoft.SmallBasic.Library.Array.SetValue(h, -1, template);
			// Array.GetValue(h, -1) = the template name
			moveDirection = 0;
			ValidateMove();
			// in: ypos, xpos, h, moveDirection ret: invalidMove = 1 or -1 or 2 if move is invalid, otherwise 0

			// See if it can be moved so that it will rotate.
			xposbk = xpos;
			yposdelta = 0;
			// move up to 3 times only
			while ((yposdelta == 0) & (Microsoft.SmallBasic.Library.Math.Abs(xposbk - xpos) < 3)) {
				// if the rotation move worked, copy the temp to "rotatedtemplate" and use that from now on
				if (invalidMove == 0) {
					basetemplate = template;
					template = "rotatedtemplate";
					Microsoft.SmallBasic.Library.Array.SetValue(h, -1, template);
					// Array.GetValue(h, -1) = the template name
					rotation = "COPY";
					CopyPiece();
					//in basetemplate, template, rotation
					yposdelta = 1;
					// Don't move down if we rotate
					MovePiece();
					//in: ypos, xpos, h
				} else if (invalidMove == 2) {
					// Don't support shifting piece when hitting another piece to the right or left.
					xpos = 99;
					// exit the loop
				} else {
					// if the rotated piece can't be placed, move it left or right and try again.
					xpos = xpos - invalidMove;
					ValidateMove();
					// in: ypos, xpos, h, moveDirection ret: invalidMove = 1 or -1 or 2 if move is invalid, otherwise 0
				}
			}

			if (invalidMove != 0) {
				xpos = xposbk;
				Microsoft.SmallBasic.Library.Array.SetValue(h, -1, basetemplate);
				// Array.GetValue(h, -1) = the template name
				template = "";
			}
		}
	}
	public static void DrawPreviewPiece()
	{
		xpos = PREVIEW_xpos;
		ypos = PREVIEW_ypos;
		h = nextPiece;

		XOFFSETBK = XOFFSET;
		YOFFSETBK = YOFFSET;
		XOFFSET = XOFFSET + Microsoft.SmallBasic.Library.Array.GetValue(Microsoft.SmallBasic.Library.Array.GetValue(h, -1), "pviewx");
		// Array.GetValue(h, -1) = the template name
		YOFFSET = YOFFSET + Microsoft.SmallBasic.Library.Array.GetValue(Microsoft.SmallBasic.Library.Array.GetValue(h, -1), "pviewy");
		// Array.GetValue(h, -1) = the template name
		MovePiece();
		//in: ypos, xpos, h

		XOFFSET = XOFFSETBK;
		YOFFSET = YOFFSETBK;
	}
	//in basetemplate, template, rotation
	public static void CopyPiece()
	{
		L = Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, "dim");

		if (rotation == (Primitive)"CW") {
			// x' = y y' = L - 1 - x
			for (i = 0; i <= BOXES - 1; i++) {
				v = Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, i);

				//x = Math.Floor(v/10)
				//y = Math.Remainder(v, 10)

				// new x and y
				x = Microsoft.SmallBasic.Library.Math.Remainder(v, 10);
				y = L - 1 - Microsoft.SmallBasic.Library.Math.Floor(v / 10);
				Microsoft.SmallBasic.Library.Array.SetValue(template, i, (x * 10) + y);
			}
		// Count-Cockwise is not currently used
		} else if (rotation == (Primitive)"CCW") {
			// x' = L - 1 - y y' = x
			for (i = 0; i <= BOXES - 1; i++) {
				v = Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, i);
				//x = Math.Floor(v/10)
				//y = Math.Remainder(v, 10)

				// new x and y
				x = L - 1 - Microsoft.SmallBasic.Library.Math.Remainder(v, 10);
				y = Microsoft.SmallBasic.Library.Math.Floor(v / 10);
				Microsoft.SmallBasic.Library.Array.SetValue(template, i, (x * 10) + y);
			}
		} else if (rotation == (Primitive)"COPY") {
			for (i = 0; i <= BOXES - 1; i++) {
				Microsoft.SmallBasic.Library.Array.SetValue(template, i, Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, i));
			}
		} else {
			GraphicsWindow.ShowMessage("invalid parameter", "Error");
			Program.End();
		}

		// Copy the remain properties from basetemplate to template.
		Microsoft.SmallBasic.Library.Array.SetValue(template, "color", Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, "color"));
		Microsoft.SmallBasic.Library.Array.SetValue(template, "dim", Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, "dim"));
		Microsoft.SmallBasic.Library.Array.SetValue(template, "pviewx", Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, "pviewx"));
		Microsoft.SmallBasic.Library.Array.SetValue(template, "pviewy", Microsoft.SmallBasic.Library.Array.GetValue(basetemplate, "pviewy"));
	}
	// in: template ret: h
	public static void CreatePiece()
	{
		// Create a new handle, representing an arrayName, that will represent the piece
		hcount = hcount + 1;
		h = System.Text.Append("piece", hcount);

		Microsoft.SmallBasic.Library.Array.SetValue(h, -1, template);
		// Array.GetValue(h, -1) = the template name

		GraphicsWindow.PenWidth = 1;
		GraphicsWindow.PenColor = "Black";
		GraphicsWindow.BrushColor = Microsoft.SmallBasic.Library.Array.GetValue(template, "color");

		for (i = 0; i <= BOXES - 1; i++) {
			s = Shapes.AddRectangle(BWIDTH, BWIDTH);
			Shapes.Move(s, -BWIDTH, -BWIDTH);
			// move off screen
			Microsoft.SmallBasic.Library.Array.SetValue(h, i, s);
		}
	}
	//in: ypos, xpos, h. ypos/xpos is 0-19, representing the top/left box coordinate of the piece on the canvas. h returned by CreatePiece
	public static void MovePiece()
	{
		for (i = 0; i <= BOXES - 1; i++) {
			v = Microsoft.SmallBasic.Library.Array.GetValue(Microsoft.SmallBasic.Library.Array.GetValue(h, -1), i);
			// Array.GetValue(h, -1) = the template name
			x = Microsoft.SmallBasic.Library.Math.Floor(v / 10);
			y = Microsoft.SmallBasic.Library.Math.Remainder(v, 10);

			// Array.GetValue(h, i) = box for piece h.
			// xpos/ypos = are topleft of shape. x/y is the box offset within the shape.
			Shapes.Move(Microsoft.SmallBasic.Library.Array.GetValue(h, i), XOFFSET + (xpos * BWIDTH) + (x * BWIDTH), YOFFSET + (ypos * BWIDTH) + (y * BWIDTH));
		}
	}
	// in: ypos, xpos, h, moveDirection ret: invalidMove = 1 or -1 or 2 if move is invalid, otherwise 0
	public static void ValidateMove()
	{
		i = 0;
		invalidMove = 0;
		while (i < BOXES) {
			v = Microsoft.SmallBasic.Library.Array.GetValue(Microsoft.SmallBasic.Library.Array.GetValue(h, -1), i);
			// Array.GetValue(h, -1) = the template name

			//x/y is the box offset within the shape.
			x = Microsoft.SmallBasic.Library.Math.Floor(v / 10);
			y = Microsoft.SmallBasic.Library.Math.Remainder(v, 10);

			if ((x + xpos + moveDirection) < 0) {
				invalidMove = -1;
				i = BOXES;
				// force getting out of the loop
			}

			if ((x + xpos + moveDirection) >= CWIDTH) {
				invalidMove = 1;
				i = BOXES;
				// force getting out of the loop
			}

			if (Microsoft.SmallBasic.Library.Array.GetValue("c", (x + xpos + moveDirection) + ((y + ypos) * CWIDTH)) != (Primitive)".") {
				invalidMove = 2;
				i = BOXES;
				// force getting out of the loop
			}

			i = i + 1;
		}
	}
	// in: ypos, xpos, h ret: done
	public static void CheckStop()
	{
		done = 0;
		i = 0;
		while (i < BOXES) {
			v = Microsoft.SmallBasic.Library.Array.GetValue(Microsoft.SmallBasic.Library.Array.GetValue(h, -1), i);
			// Array.GetValue(h, -1) = the template name

			//x/y is the box offset within the shape.
			x = Microsoft.SmallBasic.Library.Math.Floor(v / 10);
			y = Microsoft.SmallBasic.Library.Math.Remainder(v, 10);

			if (((y + ypos) > CHEIGHT) | (Microsoft.SmallBasic.Library.Array.GetValue("c", (x + xpos) + ((y + ypos) * CWIDTH)) != (Primitive)".")) {
				done = 1;
				i = BOXES;
				// force getting out of the loop
			}

			i = i + 1;
		}

		// If we need to stop the piece, move the box handles to the canvas
		if (done == 1) {
			for (i = 0; i <= BOXES - 1; i++) {
				v = Microsoft.SmallBasic.Library.Array.GetValue(Microsoft.SmallBasic.Library.Array.GetValue(h, -1), i);
				// Array.GetValue(h, -1) = the template name
				//x = Math.Floor(v/10)
				//y = Math.Remainder(v, 10)
				Microsoft.SmallBasic.Library.Array.SetValue("c", (Microsoft.SmallBasic.Library.Math.Floor(v / 10) + xpos) + ((Microsoft.SmallBasic.Library.Math.Remainder(v, 10) + ypos - 1) * CWIDTH), Microsoft.SmallBasic.Library.Array.GetValue(h, i));
			}

			// 1 points for every piece successfully dropped
			score = score + 1;
			PrintScore();

			// Delete clared lines
			DeleteLines();
		}
	}
	public static void DeleteLines()
	{
		linesCleared = 0;

		// Iterate over each row, starting from the bottom

		for (y = CHEIGHT - 1; y >= 0; y += -1) {
			// Check to see if the whole row is filled
			x = CWIDTH;
			while (x == CWIDTH) {
				x = 0;
				while (x < CWIDTH) {
					piece = Microsoft.SmallBasic.Library.Array.GetValue("c", x + (y * CWIDTH));
					if (piece == (Primitive)".") {
						x = CWIDTH;
					}
					x = x + 1;
				}

				// if non of them were empty (i.e "."), then remove the line.

				if (x == CWIDTH) {
					// Delete the line
					for (x1 = 0; x1 <= CWIDTH - 1; x1++) {
						Shapes.Remove(Microsoft.SmallBasic.Library.Array.GetValue("c", x1 + (y * CWIDTH)));
					}
					linesCleared = linesCleared + 1;

					// Move everything else down one.
					for (y1 = y; y1 >= 1; y1 += -1) {
						for (x1 = 0; x1 <= CWIDTH - 1; x1++) {
							piece = Microsoft.SmallBasic.Library.Array.GetValue("c", x1 + ((y1 - 1) * CWIDTH));
							Microsoft.SmallBasic.Library.Array.SetValue("c", x1 + (y1 * CWIDTH), piece);
							Shapes.Move(piece, Shapes.GetLeft(piece), Shapes.GetTop(piece) + BWIDTH);
						}
					}
				}
			}
		}

		if (linesCleared > 0) {
			score = score + (100 * Microsoft.SmallBasic.Library.Math.Round((linesCleared * 2.15) - 1));
			PrintScore();
		}
	}
	public static void SetupCanvas()
	{
		// GraphicsWindow.DrawResizedImage( Flickr.GetRandomPicture( "bricks" ), 0, 0, GraphicsWindow.Width, GraphicsWindow.Height)


		GraphicsWindow.BrushColor = GraphicsWindow.BackgroundColor;
		GraphicsWindow.FillRectangle(XOFFSET, YOFFSET, CWIDTH * BWIDTH, CHEIGHT * BWIDTH);

		Program.Delay(200);
		GraphicsWindow.PenWidth = 1;
		GraphicsWindow.PenColor = "Pink";
		for (x = 0; x <= CWIDTH - 1; x++) {
			for (y = 0; y <= CHEIGHT - 1; y++) {
				Microsoft.SmallBasic.Library.Array.SetValue("c", x + (y * CWIDTH), ".");
				// "." indicates spot is free
				GraphicsWindow.DrawRectangle(XOFFSET + (x * BWIDTH), YOFFSET + (y * BWIDTH), BWIDTH, BWIDTH);
			}
		}

		GraphicsWindow.PenWidth = 4;
		GraphicsWindow.PenColor = "Black";
		GraphicsWindow.DrawLine(XOFFSET, YOFFSET, XOFFSET, YOFFSET + (CHEIGHT * BWIDTH));
		GraphicsWindow.DrawLine(XOFFSET + (CWIDTH * BWIDTH), YOFFSET, XOFFSET + (CWIDTH * BWIDTH), YOFFSET + (CHEIGHT * BWIDTH));
		GraphicsWindow.DrawLine(XOFFSET, YOFFSET + (CHEIGHT * BWIDTH), XOFFSET + (CWIDTH * BWIDTH), YOFFSET + (CHEIGHT * BWIDTH));

		GraphicsWindow.PenColor = "Lime";
		GraphicsWindow.DrawLine(XOFFSET - 4, YOFFSET, XOFFSET - 4, YOFFSET + (CHEIGHT * BWIDTH) + 6);
		GraphicsWindow.DrawLine(XOFFSET + (CWIDTH * BWIDTH) + 4, YOFFSET, XOFFSET + (CWIDTH * BWIDTH) + 4, YOFFSET + (CHEIGHT * BWIDTH) + 6);
		GraphicsWindow.DrawLine(XOFFSET - 4, YOFFSET + (CHEIGHT * BWIDTH) + 4, XOFFSET + (CWIDTH * BWIDTH) + 4, YOFFSET + (CHEIGHT * BWIDTH) + 4);

		GraphicsWindow.PenColor = "Black";
		GraphicsWindow.BrushColor = "Pink";
		x = XOFFSET + (PREVIEW_xpos * BWIDTH) - BWIDTH;
		y = YOFFSET + (PREVIEW_ypos * BWIDTH) - BWIDTH;
		GraphicsWindow.FillRectangle(x, y, BWIDTH * 5, BWIDTH * 6);
		GraphicsWindow.DrawRectangle(x, y, BWIDTH * 5, BWIDTH * 6);

		GraphicsWindow.FillRectangle(x - 20, y + 190, 310, 170);
		GraphicsWindow.DrawRectangle(x - 20, y + 190, 310, 170);

		GraphicsWindow.BrushColor = "Black";
		GraphicsWindow.FontItalic = false;
		GraphicsWindow.FontName = "Comic Sans MS";
		GraphicsWindow.FontSize = 16;
		GraphicsWindow.DrawText(x, y + 200, "Game control keys:");
		GraphicsWindow.DrawText(x + 25, y + 220, "Left Arrow = Move piece left");
		GraphicsWindow.DrawText(x + 25, y + 240, "Right Arrow = Move piece right");
		GraphicsWindow.DrawText(x + 25, y + 260, "Up Arrow = Rotate piece");
		GraphicsWindow.DrawText(x + 25, y + 280, "Down Arrow = Drop piece");
		GraphicsWindow.DrawText(x, y + 320, "Press to stop game");

		Program.Delay(200);
		// without this delay, the above text will use the fontsize of the score

		GraphicsWindow.BrushColor = "Black";
		GraphicsWindow.FontName = "Georgia";
		GraphicsWindow.FontItalic = true;
		GraphicsWindow.FontSize = 36;
		GraphicsWindow.DrawText(x - 20, y + 400, "Small Basic Tetris");
		Program.Delay(200);
		// without this delay, the above text will use the fontsize of the score
		GraphicsWindow.FontSize = 16;
		GraphicsWindow.DrawText(x - 20, y + 440, "ver.0.1");

		Program.Delay(200);
		// without this delay, the above text will use the fontsize of the score
		score = 0;
		PrintScore();
	}
	public static void PrintScore()
	{
		GraphicsWindow.PenWidth = 4;
		GraphicsWindow.BrushColor = "Pink";
		GraphicsWindow.FillRectangle(500, 65, 153, 50);
		GraphicsWindow.BrushColor = "Black";
		GraphicsWindow.DrawRectangle(500, 65, 153, 50);
		GraphicsWindow.FontItalic = false;
		GraphicsWindow.FontSize = 32;
		GraphicsWindow.FontName = "Impact";
		GraphicsWindow.BrushColor = "Black";
		GraphicsWindow.DrawText(505, 70, System.Text.Append(System.Text.GetSubText("00000000", 0, 8 - System.Text.GetLength(score)), score));
	}
	public static void SetupTemplates()
	{
		// each piece has 4 boxes.
		// the index of each entry within a piece represents the box number (1-4)
		// the value of each entry represents to box zero-based box coordinate within the piece: tens place is x, ones place y

		//_X_
		//_X_
		//_XX

		Microsoft.SmallBasic.Library.Array.SetValue("template1", 0, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template1", 1, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template1", 2, 12);
		Microsoft.SmallBasic.Library.Array.SetValue("template1", 3, 22);
		Microsoft.SmallBasic.Library.Array.SetValue("template1", "color", "Yellow");
		Microsoft.SmallBasic.Library.Array.SetValue("template1", "dim", 3);
		Microsoft.SmallBasic.Library.Array.SetValue("template1", "pviewx", -12);
		Microsoft.SmallBasic.Library.Array.SetValue("template1", "pviewy", 12);


		//_X_
		//_X_
		//XX_
		Microsoft.SmallBasic.Library.Array.SetValue("template2", 0, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template2", 1, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template2", 2, 12);
		Microsoft.SmallBasic.Library.Array.SetValue("template2", 3, 2);
		Microsoft.SmallBasic.Library.Array.SetValue("template2", "color", "Magenta");
		Microsoft.SmallBasic.Library.Array.SetValue("template2", "dim", 3);
		Microsoft.SmallBasic.Library.Array.SetValue("template2", "pviewx", 12);
		Microsoft.SmallBasic.Library.Array.SetValue("template2", "pviewy", 12);


		//_X_
		//XXX
		//_
		Microsoft.SmallBasic.Library.Array.SetValue("template3", 0, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template3", 1, 1);
		Microsoft.SmallBasic.Library.Array.SetValue("template3", 2, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template3", 3, 21);
		Microsoft.SmallBasic.Library.Array.SetValue("template3", "color", "Gray");
		Microsoft.SmallBasic.Library.Array.SetValue("template3", "dim", 3);
		Microsoft.SmallBasic.Library.Array.SetValue("template3", "pviewx", 0);
		Microsoft.SmallBasic.Library.Array.SetValue("template3", "pviewy", 25);


		//XX_
		//XX_
		//_
		Microsoft.SmallBasic.Library.Array.SetValue("template4", 0, 0);
		Microsoft.SmallBasic.Library.Array.SetValue("template4", 1, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template4", 2, 1);
		Microsoft.SmallBasic.Library.Array.SetValue("template4", 3, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template4", "color", "Cyan");
		Microsoft.SmallBasic.Library.Array.SetValue("template4", "dim", 2);
		Microsoft.SmallBasic.Library.Array.SetValue("template4", "pviewx", 12);
		Microsoft.SmallBasic.Library.Array.SetValue("template4", "pviewy", 25);


		//XX_
		//_XX
		//_
		Microsoft.SmallBasic.Library.Array.SetValue("template5", 0, 0);
		Microsoft.SmallBasic.Library.Array.SetValue("template5", 1, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template5", 2, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template5", 3, 21);
		Microsoft.SmallBasic.Library.Array.SetValue("template5", "color", "Green");
		Microsoft.SmallBasic.Library.Array.SetValue("template5", "dim", 3);
		Microsoft.SmallBasic.Library.Array.SetValue("template5", "pviewx", 0);
		Microsoft.SmallBasic.Library.Array.SetValue("template5", "pviewy", 25);


		//_XX
		//XX_
		//_
		Microsoft.SmallBasic.Library.Array.SetValue("template6", 0, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template6", 1, 20);
		Microsoft.SmallBasic.Library.Array.SetValue("template6", 2, 1);
		Microsoft.SmallBasic.Library.Array.SetValue("template6", 3, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template6", "color", "Blue");
		Microsoft.SmallBasic.Library.Array.SetValue("template6", "dim", 3);
		Microsoft.SmallBasic.Library.Array.SetValue("template6", "pviewx", 0);
		Microsoft.SmallBasic.Library.Array.SetValue("template6", "pviewy", 25);


		//_X
		//_X
		//_X
		//_X
		Microsoft.SmallBasic.Library.Array.SetValue("template7", 0, 10);
		Microsoft.SmallBasic.Library.Array.SetValue("template7", 1, 11);
		Microsoft.SmallBasic.Library.Array.SetValue("template7", 2, 12);
		Microsoft.SmallBasic.Library.Array.SetValue("template7", 3, 13);
		Microsoft.SmallBasic.Library.Array.SetValue("template7", "color", "Red");
		Microsoft.SmallBasic.Library.Array.SetValue("template7", "dim", 4);
		Microsoft.SmallBasic.Library.Array.SetValue("template7", "pviewx", 0);
		Microsoft.SmallBasic.Library.Array.SetValue("template7", "pviewy", 0);
	}
}
