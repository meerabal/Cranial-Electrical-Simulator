Team 11

Name - Student Number:

Brian Yang  - 101140298
Nazeeha Harun - 101139836
Meera Balsara - 101152760
Roshan Sajja - 101168617


Responsibilities:

Brian - Use Cases - 1, 2, 3, 6, 8, Sequence Diagrams, Traceability Matrix, assisting Nazeeha with the design documents she worked on, README, Collaborating with the team on 
design decisions. 

Nazeeha - Use Cases - 4,5,7, Use Case Diagram, Textual Explanation for all use cases, UML Diagram, assisting Brian with the design documents he worked on, README, 
Collaborating with the team on design decisions, Team management and coordinating the team workflow. 

Meera - Qt code implementation and execution, collaborating with the team on design decisions, making weekly submissions to BrightSpace.

Roshan - Qt code implementation and execution, collaborating with the team on design decisions.



File Organization and Deliverables:

**All of the source code, header files, the UI file, and the project file all reside inside the “code” folder at the root of the directory. 
Inside the code folder, there are no subsequent directories to navigate through. 

**The design documentation is organized into folders inside the “Design Documentation” folder, also at the root directory. 
These sub-folders include the likes of: Use Cases, Sequence Diagrams, Traceability Matrix, UML Class Diagram, and the Textual Explanation. 
The 3004 Project use cases, sequence diagrams (8 separate files), Traceability Matrix, UML Class Diagram, and Textual Explanation can be found in these folders respectively in the form of pdf files. 

The files to be delivered include any relevant source code, header files, UI files, or project files (.pro file) to execute the QT device application. 
All of the source code integrates QT elements rather than use data structures from any C++ libraries. The code simulates all of the features specified in the Team Project 
specification file and works as intended.

The Design Documentation included in the submission includes the traceability matrix, UML class diagram, textual explanation, use cases, and all of the sequence diagrams that 
describe the implementation in more detail. In addition to the use cases themselves, there is also a use case diagram to visualize the implementation at a high level in the same document. 
All of the design documentation will include all the QT elements as well.

**NOTE: The use cases provided in the use case diagram are aligned with the manual of the actual device. Since our implementation and design decisions for some features vary from the 
manual, these differences have been described in detail in the textual explanation and traceability matrix, which are more reflective of the implementation itself.   



How to run the program (Basic Tested Scenarios):

(** Note: General run down on how to use the device, user should note more details from the traceability matrix for thorough testing of all possible scenarios including the advanced ones, all of which work as expected):

1. To untar the submission folder, the user can type: tar -xvf team11.tar from the command line. 
2. Open the comp3004_fp.pro file from the ‘code’ folder from within Qt in the course VM. Click on the run button to observe the GUI.
3. Press and hold the power button for a few seconds to turn the device on.
4. Once turned on, click (not hold) on the power button to switch between the session groups.
5. Use the UP and DOWN arrows to select the session type. 
6. Click ‘Select’ to begin the therapy session. 
7. Observe the connection test happening for five seconds and then the session will begin.
8. Once the session has begun, UP and DOWN buttons can now be used to change the intensity.
9. The connection test’s slider may be adjusted to simulate a change in connection. 
10. Once the session naturally ends, the user may choose to press the ‘Record Session’ button to add the therapy session to history.
11. Press and hold the power button for a few seconds to turn the device off, or if desired, the user can begin another session by repeating everything from step 4.
12. If the battery is critically low, the user needs to close and restart the program.
