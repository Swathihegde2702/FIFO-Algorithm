# FIFO-Algorithm
Visual Representation FIFO Page Replacement Algorithm

The FIFO page replacement algorithm is a technique used in operating system
to manage memory and allocate resources efficiently. The principle of the algorithm
is first page that enters the memory is the first one to be replaced when page fault
occurs. This project demonstrates the FIFO Page Replacement by creating graphical
interface using OPENGL and GLUT libraries in c. Users can visualize the behavior
and efficiency of the algorithm. The program initializes the number of frames, pages
and allow user to input sequence of page reference, then it iterates each page
reference and checks whether page is already present in the frame or not. If page is
not found it replace the oldest page in the frame with current page and increment the
page fault count. The animation is achieved by timer and keyboard function. At the
end total number of page faults will be displayed.

 Steps to Run Project in Terminal(ubuntu)
 1. gedit fifo.c(To open file)
 2. gcc fifo.c -lGL -lGLU -lglut
 3. ./a.out
     
 
