#include "main.h"
#include "AutonomousAction.h"
#include "PositionTracker.h"
#include "Store.h"
#include "ScoreTopGoal.h"
#include "ScoreMidGoal.h"
#include "ScoreLowGoal.h"
#include "LittleWillDown.h"
#include "LittleWillUp.h"
#include "DriveAction.h"
#include <memory>
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
	pros::lcd::initialize();

	//pros::lcd::register_btn1_cb(on_center_button);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {

}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purpo ses.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
	//Sets start position
	PositionTracker::setPosition(0.0, 0.0, 0.0);

	//Autonomous Instructions List
	//Example -> actions.push_back(std::make_unique<TaskExample>(pros::millis(), (uint32_t)10000));
	std::vector<std::unique_ptr<AutonomousAction>> actions;
	

	std::vector<std::unique_ptr<AutonomousAction>>::iterator it = actions.begin();
	while(true) {
		if (it == actions.end()) break;
		PositionTracker::updatePosition();

		int result = (*it) -> run();
		if (result == 1) it = actions.erase(it);
		
		pros::delay(15);
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
	pros::Controller master(pros::E_CONTROLLER_MASTER);
	pros::MotorGroup left_mg({10, -9, 8});    // Creates a motor group with forwards ports 1 & 3 and reversed port 2
	pros::MotorGroup right_mg({-3, 2, -1});  // Creates a motor group with forwards port 5 and reversed ports 4 & 6
	pros::Motor intake1(12);
	pros::Motor intake2(-13);
	pros::Motor intake3(-14);
	pros::adi::DigitalOut will(7);

	bool down_arrw;
	bool up_arrw;
	bool r1;
	bool r2;
	bool l1;
	bool l2;

	while (true) {
		/*pros::lcd::print(0, "%d %d %d", (pros::lcd::read_buttons() & LCD_BTN_LEFT) >> 2,
		                 (pros::lcd::read_buttons() & LCD_BTN_CENTER) >> 1,
		                 (pros::lcd::read_buttons() & LCD_BTN_RIGHT) >> 0);  // Prints status of the emulated screen LCDs*/

		// Arcade control scheme
		int dir = master.get_analog(ANALOG_RIGHT_Y);    // Gets amount forward/backward from left joystick
		int turn = master.get_analog(ANALOG_LEFT_X);  // Gets the turn left/right from right joystick
		left_mg.move(dir - turn);                      // Sets left motor voltage
		right_mg.move(dir + turn);                     // Sets right motor voltage

		down_arrw = master.get_digital_new_press(DIGITAL_DOWN);
		up_arrw   = master.get_digital_new_press(DIGITAL_UP);
		r1 = master.get_digital(DIGITAL_R1);
		r2 = master.get_digital(DIGITAL_R2);
		l1 = master.get_digital(DIGITAL_L1);
		l2 = master.get_digital(DIGITAL_L2);
		
		if (down_arrw) will.set_value(1);
		if (up_arrw) will.set_value(0);

		if(r1 || r2 || l1 || l2) {
			if (r1 && !(r2 || l1 || l2)) { intake1.move(127);  intake2.move(127);  intake3.move(0);    }
			if (r2 && !(r1 || l1 || l2)) { intake1.move(127);  intake2.move(127);  intake3.move(127);  }
			if (l1 && !(r1 || l2 || l2)) { intake1.move(127);  intake2.move(-127); intake3.move(-127); }
			if (l2 && !(r1 || r2 || l1)) { intake1.move(-127); intake2.move(-127); intake3.move(-127); }
		} else { intake1.move(0); intake2.move(0); intake3.move(0); }

		pros::delay(20);                               // Run for 20 ms then update
	}
}