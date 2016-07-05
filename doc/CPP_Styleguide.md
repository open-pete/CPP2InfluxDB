#C++ - Styleguide
##Naming of identifiers
- Identifiers have to depend on the purpose the variable, function, constant, ... has to serve. **Always** choose a longer identifier, which describes the purpose better, than a short and easy to use identfier that does not show the clear purpose.
- Every new Word in an identifier, except for the first is starting with a **capital letter** (except for names of constants).
	- right : get**A**ddress()
    - wrong : get**a**ddress()  

- Identifiers never contain a **_** , except for the very last letter in parameters (and except for names of constants).
	- right : ge**tA**ddress(int pos**tC**ode_)
	- wrong : ge**t_A**ddress(int pos**t_C**ode_) 

- Names of **functions, variables, and parameters** always start with a **small** letter
	- functions :
        - right : **g**etAddress()
        - wrong : **G**etAddress() 
    - variables :
    	- right : int **h**ousesCount
    	- wrong : int **H**ousesCount
    - parameters :
    	- right : getAddress(int **p**ostCode_)
    	- wrong : getAddress(int **P**ostCode_)

- Names of **Classes, Enums, Structs, Contructors and Destructors** always start with a capital letter:
	- right :

```
class Car {
    public:
        Car();
	// ...
}
```
 - 
	- wrong :


```
class car {
    public:
        car();
	// ...
}
``` 

- **parameters** do always end with a **_**
	- right : getAddress(int postCode**_**)
	- wrong : getAddress(int postCode)

- **constants**
	- every letter of a name of a constant is capital, every word is seperated by a **_**
		- right : const bool SHOW_IN_DETAIL = false; 
		- wrong : const bool showInDetail = false; 

##Functions
- Functions are ordered by use. 
- The structure of order has two layers.
	- The first layer is encapsulated by ** /\* --- layer1 --- \*/ **
	- The second layer is started by ** // layer 1.1 ** 
	- for example:

```
	/* --- simulation --- */
    // simulation
    void startSimulation(int moleculeAbstractionFactor_);
    void simulateTimeStep(float timeStepInSeconds_);

    // calculation of forces
    void startSimulation(int moleculeAbstractionFactor_);
    void simulateTimeStep(float timeStepInSeconds_);

    // calculation of forces
    void clearForce();
    void addForce(vector3 force_);
    vector3 getForce();


    /* --- getters and setters --- */
    // setters
    void setMoleculesCount(float val_)          {moleculesCount = val_;            };
    void setSimulatedMoleculesCount(float val_) {simulatedMoleculesCount = val_;   };
    void setTemperature(float val_)             {temperature = val_;               };
```

- getters and setters are always the very last functions


##Declaration and implementation
- every class, with all his functions and attributes is declarated in a header-file
- all functions except for getters and setters are implemented in a *.cpp - file
- if structs and constants do not directly belong to a class define them in the Types.h - file

##OOP (object - oriented - programming)
- Information - hiding
	- every class attribute **must** be private
	- class attributes are only read and modified by getters and setters. **No** private class attribute is read or modified directly.
	- every function, that is used only within the class has to be private

##Documentation
- Every file is documented by a ccDoc - comment (=java-doc) at the beginning of the file
	- example :

```
/**
    Car.h
    Purpose: Defines Class Car

    @author anon
    @version 1.0
    @since 2045-11-20
*/
```


- Every Function is documented by a ccDoc - comment (=java-doc) directly in front of the implementation of the function.
	- example : 

```
/**
 * @brief Returns an Image object that can then be painted on the screen.
 * 
 * @param  url_  an absolute URL giving the base location of the image
 * @param  name_ the location of the image, relative to the url argument
 * @return      the image at the specified URL
 * @see         Image
 *  
 * Returns an Image object that can then be painted on the screen. 
 * The url argument must specify an absolute {@link URL}. The name
 * argument is a specifier that is relative to the url argument. 
 * <p>
 * This method always returns immediately, whether or not the 
 * image exists. When this applet attempts to draw the image on
 * the screen, the data will be loaded. The graphics primitives 
 * that draw the image will incrementally paint on the screen. 
 */
 public Image getImage(URL url_, String name_) {
 	return getImage(new URL(url_, name_));
 }
```

- The code has to be documented by inline-comments. Use as much documentation as possible. But do not write more documentation as code.

##Testing
- Every function needs a Unit-Test.
- Every bug needs a Unit-Test.

##Version Control
- Add a git repository for your project.
- Commit every **finished** step of coding.
