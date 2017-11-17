# SWPD
Plagiarism Detector for SolidWorks files... (or anything?)

## Topics for discussion
* **GUI?** I'm really tempted to have us make this a GUI app. (Kiesel)
* **Python GUI?** I'm equally tempted to do the GUI stuff in something easy like Python and have the big data processing guts use C++.

## Basic plan (non-GUI part)
The program needs to perform a series of tasks
1. Given a directory, enumerate every file in the directory
2. Read each file into a byte array
3. For each pair of arrays:
   1. Run a thread object for that pair to perform **the comparison**.
4. Join all threads to let them finish.
5. Read results from all created threads.
6. Do data analysis on the results to determine prospective plagiarism targets.
