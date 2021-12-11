Test
Team 1
Authors:
William Wright (10104993)
Mahmoud Sabaayon (101129493)
Anwar Kulane (101143398)
Soorya Balaji (101148424)

Team Work:
We have utilized an agile teamwork strategy (pair programming); whereby all of the members focus on the same part of the program at a time, with one member writing the code and the rest contributing to implementing algorithms/code structure/program design as well as debugging.
We have found that this form of teamwork was best suited for a small-scale project as it allowed us to efficiently and quickly proceed with each chunk of code/design. With William Wright writing the code, and the rest equally contributing to each part of the project.

Tested Scenarios:
	All use cases have been tested and work well. We also have a testing class that goes into detail with testing(TestCases.cpp).

All testing was done manually through the GUI or automatically through test cases. Whenever an update was made, we ran the test cases to make sure that everything was still working fine.


As for the manual testing, here’s what we tested:
Therapy session completes and shuts down
User is able to record/load the recording
User is able to select their desired settings (wave, frequency, current, etc)
The GUI displays the information correctly
The user cannot modify the values while the therapy is running if the locked feature is on
The battery is draining while the therapy is running and shuts down at 2%
The user cannot turn it back on if the battery is <= 2%
The VM does not have a QSound feature, so we did the low battery test by sending a qDebug() to the console.
The device shuts down if the amperage is > 700 (use debugging window implemented in the GUI)


/
	README.md
	images.qrc
	CESSimulator.pro
/Documentation
	sequenceDiagram.pdf
	Traceability Matrix.pdf
	Use Cases.pdf
	classDiagram.pdf
/src
	ces.cpp
	timer.cpp
	loggingwidget.cpp
	mainscreenwidget.cpp
	mainwindow.cpp
	main.cpp
	testcases.cpp
/header
	ces.h
	timer.h
	loggingwidget.h
	mainscreenwidget.h
	mainwindow.h
	testcases.h
/ui
	debugconsole.ui
	loggingwidget.ui
	mainscreenwidget.ui
	mainwindow.ui
/images
	battery-0.png
	battery-1.png
	battery-2.png
	battery-3.png
	battery-4.png
	battery-5.png
	clock.png
	down.png
	icons8-lock-24.png
	icons8-lock-48.png
	on-off-button.png
	power.png
	rec.png
	timer.png
