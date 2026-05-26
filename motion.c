
#include "motion.h"
#include "launchpad.h"
#include <driverlib/gpio.h>

/*

// motion sensor structure to manage states.
typedef struct {
    Event *callback_event;          // pointer to Event object
    uint32_t raw_input;             // the raw input from GPIO port pin
    bool new_input;                 // flag for new input data
} MotionSensorState;
*/

typedef struct {
    Event *callback_event;          // pointer to Event object
    uint32_t raw_input;             // the raw input from GPIO port pin
    bool new_input;                 // flag for new input data
} MotionSensorState;

// motion_sensor state object
MotionSensorState motion_sensor;

// forward declaration(s)
static void MotionSensorISR();      //used in: void MotionSensorInit()



// Initialize motion sensor
void MotionSensorInit()
{
    // initialize the state structure
    motion_sensor.callback_event = NULL; // invalid event upon initialization
    motion_sensor.new_input = false;      // no new input, so default to false

    // Enable Port C peripheral and configure pin 4 of port C as an input pin
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE, GPIO_PIN_4);

    // initialize the ISR and allow for interrupt handling
    GPIOIntRegister(GPIO_PORTC_BASE, MotionSensorISR);              //register the interrupts from port C to be handled by MotionSensorISR
    GPIOIntTypeSet(GPIO_PORTC_BASE, GPIO_PIN_4, GPIO_BOTH_EDGES);   //set the edge form (type set) that will be registered as a change for interrupts
    IntPrioritySet(INT_GPIOC, 1);                                   //set the interrupt priority level to 0
    GPIOIntEnable(GPIO_PORTC_BASE, GPIO_PIN_4);                     //enable interrupts for the port and pin pair
}
// Motion Sensor Interrupt Event Registration
void MotionSensorEventRegister(Event* callback_event)
{
    assert(EventInitialized(callback_event));       // verifies the event is initialized (throws error when not)
    motion_sensor.callback_event = callback_event;  // sets the motion sensors state structure callback_event to what was given (if initialized and it is a new input)
}







// Motion Sensor ISR (called every time an interrupt is produced from PC)
static void MotionSensorISR(){
    // get and record the raw data (no need to buffer or invert)
    motion_sensor.raw_input = GPIOPinRead(GPIO_PORTC_BASE, GPIO_PIN_4);
    //schedule the callback interrupt if valid event
    if (motion_sensor.callback_event != NULL) {
        EventSchedule(motion_sensor.callback_event, EventGetCurrentTime()+5);
    }

    //clear the interrupt flag for the port & pin pair after callback has been scheduled to allow for return
    GPIOIntClear(GPIO_PORTC_BASE, GPIO_PIN_4);
}
// Method for Reading and returning what to do with the sensor value
int ReadMotionSensor(){

    motion_sensor.new_input = ReadMotionSensorASM();
    if(motion_sensor.new_input){
        motion_sensor.new_input = false;
        return 1;
    }
    return 0;
}


