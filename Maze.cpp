#include "Maze.h"
#include "Color.h"
#include "Rect.h"

#include <windows.h>
//#include <iostream>
//using namespace std;

//look at line 156 and 157!

Maze::Maze(Matrix* mz)
{
   maze = mz;

   WALL = 0;
   SPACE = 1;
   TRIED = 2;
   BACKTRACK = 3;
   PATH = 4;
}

Maze::~Maze()
{
   delete maze;
}

void Maze::addListener(Update* g)
{
   gui = g;
}

bool Maze::solve()
{
   bool done = traverse(1, 1);
   return done;
}

bool Maze::traverse(int row, int col)
{
   bool done = false; //assume we are not done unless proven otherwise

   //test that the current grid location is a space (i.e. not a wall or already tried)
   if (maze->getElement(row, col) == SPACE)
   {
      //now it has been tried so mark it as tried

	  maze->setElement(row, col, TRIED);

		Sleep(75);	
		//Sleep(5);  //to slow it down

      gui->update();

      //check to see if we have arrived at the bottom right corner of the maze
      int height = maze->getNumRows();
      int width = maze->getNumCols();

      if (col == width && row == height)
      {
        done = true;
      }
      else
      {
        //make recursive calls that consider all four orthogonal directions

		//used this so I wouldn't have to write 4 if statements
		//made the path direction the same as Lab 06
		
		      //right					//Up                       //left                    //down
		while(traverse(row + 1, col) || traverse(row, col + 1)  || traverse(row - 1, col) || traverse(row, col - 1))
		{
			done = true;
			break;
		}
		
      }

      //if we are done, on the way back recursively we must mark the path that we took as the solution path
      if (done)
      {
            //mark the path taken as the solution path
			maze->setElement(row, col, PATH);

			gui->update();
      }
      //backtrack
      else
      {
         //DO THIS
			maze->setElement(row, col, BACKTRACK);

		Sleep(75);
		//Sleep(5);
         gui->update();
      }
   }

   return done;
}

void Maze::mouseClicked(int x, int y)
{}

void Maze::draw(wxDC& dc, int width, int height)
{
   int rows = maze->getNumRows();
   int cols = maze->getNumCols();
   int cell_width = (int) (((double) width)/cols + 0.5);
   int cell_height = (int) (((double) height)/rows + 0.5);

   Color red(1.0, 0.0, 0.0);
   Rect redRect(&red, cell_width, cell_height);

   Color green(0.0, 1.0, 0.0);
   Rect greenRect(&green, cell_width, cell_height);

   Color blue(0.0, 0.0, 1.0);
   Rect blueRect(&blue, cell_width, cell_height);

   Color white(1.0, 1.0, 1.0);
   Rect whiteRect(&white, cell_width, cell_height);

   Color black(0.0, 0.0, 0.0);
   Rect blackRect(&black, cell_width, cell_height);
 
   for (int i = 1; i <= rows; i++)
   {
      for (int j = 1; j <= cols; j++)
      {
         int val = (int) maze->getElement(i, j);
         int x_pixel = (j - 1) * cell_width + cell_width/2;
         int y_pixel = (i - 1) * cell_height + cell_height/2;

         if (val == WALL)
         {
            blackRect.draw(dc, x_pixel, y_pixel);
         }
         else if (val == SPACE)
         {
            whiteRect.draw(dc, x_pixel, y_pixel);
         }
         else if (val == TRIED)
         {
            blueRect.draw(dc, x_pixel, y_pixel);
         }
         else if (val == BACKTRACK)
         {
			redRect.draw(dc, x_pixel, y_pixel);            
			//whiteRect.draw(dc, x_pixel, y_pixel); //Didn't like it filling in red
         }
         else if (val == PATH)
         {
            greenRect.draw(dc, x_pixel, y_pixel);
         }
      }
   }
}
