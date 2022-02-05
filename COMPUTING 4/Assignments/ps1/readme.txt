/**********************************************************************
*  ps1-readme template                                                   
*  Recursive Graphics Assignment                       
**********************************************************************/
Your name: Phong Hong Vo

Operating system you're using (Linux, OS X, or Windows): Windows and Linux

If Windows, which solution?: Windows 10


Text editor or IDE you're using: notepad++ and Vim

Hours to complete assignment: 14 hrs

/**********************************************************************
*  Discussion (important)
*  About what you did—at least 100 words (what you actually implemented)

My combo program has two sub functional codes that implement an original 
and a sierpinski triangle fractal.
For the original sub-function, I program that yields an octagon-in-octagon shape 
    which every single octagon is being repeatively contained by the outer one.
    To make it, I let each corner's point is a mid-point of the outer octagon's edge.
    Then I repeat the code to make another inner octagon right in the previously made     octagon.
For the sierpinski, first of all, I make a prime triangle fits with the window's size     entered (depth = 0). 
    Then my program makes a certain of quantity of triangles that implements the second depth (depth = 1). These triangles (tri1, tri1 and tri3) are set at the sub triangles of the sub-parts which were created by the previous recursive.
    Repeat the code with the depth be 2, 3 and so on until the depth meets the entered input.

**********************************************************************/

/**********************************************************************
*  List whatever help (if any) you received from TAs, the instructor,
*  classmates, or anyone else. There was nothing.
**********************************************************************/

/**********************************************************************
* Describe what was interesting, hard, fun, or easy about your project.
I found it interesting in this project as I was working on the octagons.
I had to make sure the exact coordinates of each single points of each octagon to make sure it would be the midpoints of the outer octagon' edges.

**********************************************************************/

/**********************************************************************
* List any other comments here.                                     
**********************************************************************/