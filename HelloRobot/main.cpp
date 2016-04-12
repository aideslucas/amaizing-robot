/*

* main.cpp

*

*  Created on: Jan 10, 2015

*      Author: colman

*/

#include <libplayerc++/playerc++.h>

using namespace PlayerCc;

using namespace std;

int main()

{

    // Connecting to simulation

    PlayerClient pc("localhost", 6665);

    // Using a laser

    //LaserProxy lp(&pc);

    // Using a sonar

    SonarProxy sp(&pc);

    // The robot's position

    Position2dProxy pp(&pc);

    // Starting real robot's motor

    //pp.SetMotorEnable(true);

    // Setting speed and angle to be used

    float speed = 0.5;

    float angle = 0.0;

    // Obstacle position

    double Xobs = 0.0;

    double Yobs = 0.0;

    // Sensor angle, relative to robot

//    int AngleVec[5] = {90, 25, 0, -25, -90};

    int radAngleVec[5] = {dtor(90), dtor(25), dtor(0), dtor(-25), dtor(-90)};



    // Keep the robot going

    while (true)

    {

        // Initializing speed

        speed = 1.0;

        // Initializing angle

        angle = 0.0;

        pc.Read();

        // Output robot's current X,Y locations and angle

        cout << "X: "     << pp.GetXPos()

            << ", Y: "   << pp.GetYPos()

            << ", Yaw: " << pp.GetYaw() << endl;

        // Output robot's sonar data

        cout << sp << endl;

        // Checking for obstacles in path

        // If there is an obstacle on the RIGHT (90 deg)

        if (sp[0] < 0.8)

        {

            // Adjust speed

            speed -= 0.1;

            // Adjust angle

            angle += 0.6 * ( 1 - sp[0]);

            // Set obstacle position

            Xobs = pp.GetXPos() + (sp[0] * cos(pp.GetYaw() + radAngleVec[0]));

            Yobs = pp.GetYPos() + (sp[0] * cos(pp.GetYaw() + radAngleVec[0]));


            // Notify about the current obstacle

            cout << "There is an obstacle to my right (90), "

                << sp[0]     << " away."

                << " At X: " << Xobs

                << ", Y: "   << Yobs << endl;

        }

        // If there is an obstacle on the RIGHT (25 deg)

        if (sp[1] < 0.8)

        {

            // Adjust speed

            speed -= 0.2;

            // Adjust angle

            angle += 0.8 * (1 - sp[1]);

            // Set obstacle position

            Xobs = pp.GetXPos() + (sp[1] * cos(pp.GetYaw() + radAngleVec[1]));

            Yobs = pp.GetYPos() + (sp[1] * cos(pp.GetYaw() + radAngleVec[1]));


            // Notify about the current obstacle

            cout << "There is an obstacle to my right (25), "

                << sp[1]     << " away."

                << " At X: " << Xobs

                << ", Y: "   << Yobs << endl;

        }

        // If there is an obstacle on the Front (0 deg)

        if (sp[2] < 0.8)

        {

            // Adjust speed

            speed -= 0.3;

            // Find the clearest path

            // If right is more clear, adjust right

            if ((sp[1] + sp[0]) > (sp[3] + sp[4]))

            {

                // Adjust angle

                angle -= 1 - sp[2];

            }

            // If left is more clear, adjust left

            else

            {

                // Adjust angle

                angle += 1 - sp[2];

            }


            // Set obstacle position

            Xobs = pp.GetXPos() + (sp[2] * cos(pp.GetYaw() + radAngleVec[2]));

            Yobs = pp.GetYPos() + (sp[2] * cos(pp.GetYaw() + radAngleVec[2]));


            // Notify about the current obstacle

            cout << "There is an obstacle to my right (0), "

                << sp[2]     << " away."

                << " At X: " << Xobs

                << ", Y: "   << Yobs << endl;

        }

        // If there is an obstacle on the LEFT (-25 deg)

        if (sp[3] < 0.8)

        {

            // Adjust speed

            speed -= 0.2;

            // Adjust angle

            angle -= 0.8 * (1 - sp[3]);

            // Set obstacle position

            Xobs = pp.GetXPos() + (sp[3] * cos(pp.GetYaw() + radAngleVec[3]));

            Yobs = pp.GetYPos() + (sp[3] * cos(pp.GetYaw() + radAngleVec[3]));


            // Notify about the current obstacle

            cout << "There is an obstacle to my right (-25), "

                << sp[3]     << " away."

                << " At X: " << Xobs

                << ", Y: "   << Yobs << endl;

        }

        // If there is an obstacle on the LEFT (-90 deg)

        if (sp[4] < 0.8)

        {

            // Adjust speed

            speed -= 0.1;

            // Adjust angle

            angle -= 0.6 * (1 - sp[4]);


            // Set obstacle position

            Xobs = pp.GetXPos() + (sp[4] * cos(pp.GetYaw() + radAngleVec[4]));

            Yobs = pp.GetYPos() + (sp[4] * cos(pp.GetYaw() + radAngleVec[4]));


            // Notify about the current obstacle

            cout << "There is an obstacle to my right (-90), "

                << sp[4]     << " away."

                << " At X: " << Xobs

                << ", Y: "   << Yobs << endl;

        }

        // Set the robot with the new speed and angle

        pp.SetSpeed(speed, angle);

    }

    return 0;

}
