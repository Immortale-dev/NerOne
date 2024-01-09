
![NerOne](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/logo.svg?raw=true#gh-light-mode-only)
![NerOne](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/logo_dark.svg?raw=true#gh-dark-mode-only)

___
Low level **C++** neural network engine. The engine provides a huge flexibility in creating neural networks.

Even more flexibility were provided in **v2** comparing to previous version!

## Table of Contest
* [Table of Contest](#table-of-contest)
* [Build](#build)
* [Documentation](#documentation)
	* [Definitions](#definitions)
	* [Types and aliases](#types-and-aliases)
	* [class nerone::value::Value](#class-neronevaluevalue)
	* [class nerone::value::FValue<T>](#class-neronevaluefvaluet)
		* [virtual T get() = 0](#virtual-t-get--0)
		* [virtual void set(T value) = 0](#virtual-void-sett-value--0)
	* [class nerone::value::GValue<T>](#class-neronevaluegvaluet)
		* [virtual T get_grad() = 0](#virtual-t-get_grad--0)
		* [virtual void set_grad(T value) = 0](#virtual-void-set_gradt-value--0)
	* [class nerone::value::Cumulative<T>](#class-neronevaluecumulativet)
		* [T get()](#t-get)
		* [void set(T value)](#void-sett-value)
		* [get_grad()](#get_grad)
		* [set_grad(T value)](#set_gradt-value)
		* [virtual void pop()](#virtual-void-pop)
		* [virtual void clean()](#virtual-void-clean)
		* [virtual bool empty()](#virtual-bool-empty)
	* [nerone::cell::Cell](#neronecellcell)
		* [virtual const value_list_t& get_inputs() = 0](#virtual-const-value_list_t-get_inputs--0)
		* [virtual const value_list_t& get_outputs() = 0](#virtual-const-value_list_t-get_outputs--0)
		* [virtual void set_inputs(value_list_t vals) = 0](#virtual-void-set_inputsvalue_list_t-vals--0)
		* [virtual void set_outputs(value_list_t vals) = 0](#virtual-void-set_outputsvalue_list_t-vals--0)
	* [nerone::cell::VCell<VT>](#neronecellvcellvt)
	* [nerone::cell::OCell<VT>](#neronecellocellvt)
		* [virtual void calc_value() = 0](#virtual-void-calc_value--0)
		* [virtual void calc_grad() = 0](#virtual-void-calc_grad--0)
		* [virtual void clean() = 0](#virtual-void-clean--0)
		* [virtual void command(shared_cell_command_t command)](#virtual-void-commandshared_cell_command_t-command)
		* [virtual void start()](#virtual-void-start)
		* [void finish()](#void-finish)
	* [nerone::cell::TCell<VT>](#neronecelltcellvt)
		* [virtual const weight_list_t& get_weights() = 0](#virtual-const-weight_list_t-get_weights--0)
		* [virtual void set_weights(weight_list_t weights) = 0](#virtual-void-set_weightsweight_list_t-weights--0)
		* [virtual void update(shared_train_data_t data) = 0](#virtual-void-updateshared_train_data_t-data--0)
	* [nerone::cell::Functional<VT, FN>](#neronecellfunctionalvt-fn)
		* [Functional()](#functional)
		* [Functional(shared_value_t input, shared_value_t output)](#functionalshared_value_t-input-shared_value_t-output)
		* [Functional(FN act, FN grad)](#functionalfn-act-fn-grad)
		* [Functional(shared_value_t input, shared_value_t output, FN act, FN grad)](#functionalshared_value_t-input-shared_value_t-output-fn-act-fn-grad)
		* [Functional(shared_value_t input, FN act, FN grad)](#functionalshared_value_t-input-fn-act-fn-grad)
		* [FN get_act_fn()](#fn-get_act_fn)
		* [FN get_grad_fn()](#fn-get_grad_fn)
		* [void set_act_fn(FN)](#void-set_act_fnfn)
		* [void set_grad_fn(FN)](#void-set_grad_fnfn)
		* [const value_list_t& get_inputs()](#const-value_list_t-get_inputs)
		* [const value_list_t& get_outputs()](#const-value_list_t-get_outputs)
		* [void set_inputs(value_list_t vals)](#void-set_inputsvalue_list_t-vals)
		* [void set_outputs(value_list_t vals)](#void-set_outputsvalue_list_t-vals)
		* [void set_input(shared_value_t value)](#void-set_inputshared_value_t-value)
		* [void set_output(shared_value_t value)](#void-set_outputshared_value_t-value)
		* [void clean()](#void-clean)
	* [nerone::cell::Activation<VT>](#neronecellactivationvt)
		* [void calc_value()](#void-calc_value)
		* [void calc_grad()](#void-calc_grad)
	* [nerone::cell::Loss](#neronecellloss)
		* [void calc_value(typename value_type::f_type expected)](#void-calc_valuetypename-value_typef_type-expected)
		* [void calc_value()](#void-calc_value-1)
		* [void calc_grad()](#void-calc_grad-1)
		* [void clean()](#void-clean-1)
		* [void set_expected_value(shared_value_t val)](#void-set_expected_valueshared_value_t-val)
		* [shared_value_t get_expected_value()](#shared_value_t-get_expected_value)
	* [nerone::cell::Segment<VT>](#neronecellsegmentvt)
		* [Segment(value_list_t inputs, value_list_t outputs)](#segmentvalue_list_t-inputs-value_list_t-outputs)
		* [const value_list_t& get_inputs()](#const-value_list_t-get_inputs-1)
		* [const value_list_t& get_outputs()](#const-value_list_t-get_outputs-1)
		* [void set_inputs(value_list_t vals)](#void-set_inputsvalue_list_t-vals-1)
		* [void set_outputs(value_list_t vals)](#void-set_outputsvalue_list_t-vals-1)
		* [void calc_value()](#void-calc_value-2)
		* [void calc_grad()](#void-calc_grad-2)
		* [void clean()](#void-clean-2)
		* [const weight_list_t& get_weights()](#const-weight_list_t-get_weights)
		* [void set_weights(weight_list_t weights)](#void-set_weightsweight_list_t-weights)
		* [void update(shared_train_data_t data)](#void-updateshared_train_data_t-data)
	* [nerone::cell::Cluster<VT>](#neronecellclustervt)
		* [Cluster(cell_list_t cells)](#clustercell_list_t-cells)
		* [void update(shared_train_data_t data)](#void-updateshared_train_data_t-data-1)
		* [void calc_value()](#void-calc_value-3)
		* [void calc_grad()](#void-calc_grad-3)
		* [void clean()](#void-clean-3)
		* [void start()](#void-start)
		* [void finish()](#void-finish-1)
		* [void command(shared_cell_command_t com)](#void-commandshared_cell_command_t-com)
		* [const weight_list_t& get_weights()](#const-weight_list_t-get_weights-1)
		* [void set_weights(weight_list_t weights)](#void-set_weightsweight_list_t-weights-1)
		* [virtual const cell_list_t& get_cells()](#virtual-const-cell_list_t-get_cells)
		* [virtual void set_cells(cell_list_t cells)](#virtual-void-set_cellscell_list_t-cells)
	* [nerone::cell::Layer<VT>](#neronecelllayervt)
		* [Layer(cell_list_t cells)](#layercell_list_t-cells)
		* [const value_list_t& get_inputs()](#const-value_list_t-get_inputs-2)
		* [const value_list_t& get_outputs()](#const-value_list_t-get_outputs-2)
		* [void set_inputs(value_list_t vals)](#void-set_inputsvalue_list_t-vals-2)
		* [void set_outputs(value_list_t vals)](#void-set_outputsvalue_list_t-vals-2)
	* [nerone::cell::Sequense<VT>](#neronecellsequensevt)
		* [Sequence(cell_list_t cells)](#sequencecell_list_t-cells)
		* [const value_list_t& get_inputs()](#const-value_list_t-get_inputs-3)
		* [const value_list_t& get_outputs()](#const-value_list_t-get_outputs-3)
		* [void set_inputs(value_list_t vals)](#void-set_inputsvalue_list_t-vals-3)
		* [void set_outputs(value_list_t vals)](#void-set_outputsvalue_list_t-vals-3)
		* [void connect_cells()](#void-connect_cells)
	* [nerone::cell::LossLayer<VT>](#neronecelllosslayervt)
		* [LossLayer(cell_list_t cells)](#losslayercell_list_t-cells)
		* [const value_list_t& get_expected_inputs()](#const-value_list_t-get_expected_inputs)
		* [void set_expected_inputs(value_list_t vals)](#void-set_expected_inputsvalue_list_t-vals)
	* [nerone::Producer<VT>](#neroneproducervt)
		* [Producer(body_cell_t body, loss_cell_t loss)](#producerbody_cell_t-body-loss_cell_t-loss)
		* [virtual void set_body_cell(body_cell_t body)](#virtual-void-set_body_cellbody_cell_t-body)
		* [virtual void set_loss_cell(loss_cell_t loss)](#virtual-void-set_loss_cellloss_cell_t-loss)
		* [virtual body_cell_t get_body_cell()](#virtual-body_cell_t-get_body_cell)
		* [virtual loss_cell_t get_loss_cell()](#virtual-loss_cell_t-get_loss_cell)
	* [nerone::GDProducer](#neronegdproducer)
	* [Activation functions](#activation-functions)
	* [class nerone::activation::Sigmoid](#class-neroneactivationsigmoid)
	* [class nerone::activation::ReLU<R>](#class-neroneactivationrelur)
	* [class nerone::activation::TanH](#class-neroneactivationtanh)
	* [class nerone::activation::ELU](#class-neroneactivationelu)
	* [class nerone::activation::GELU](#class-neroneactivationgelu)
	* [class nerone::activation::SELU](#class-neroneactivationselu)
	* [class nerone::activation::Swish](#class-neroneactivationswish)
	* [Loss functions](#loss-functions)
	* [class nerone::loss::MeanSquareError](#class-neronelossmeansquareerror)
	* [class nerone::loss::CrossEntropy](#class-neronelosscrossentropy)
* [Usage example](#usage-example)
* [Tests](#tests)
	* [2 Zones problem (from the example in previous section)](#zones-problem-from-the-example-in-previous-section)
	* [4 Zones problem](#zones-problem)
	* [Circle problem](#circle-problem)
	* [Spiral problem](#spiral-problem)
* [Additional information](#additional-information)
* [License](#license)

## Build
Library was tested using **GNU G++** compiler with flag **-std=c++17**. So it is recommended to use C++ 17 or higher version of compiler. Compiling by other compilers may require code corrections.

`make` default command builds the tests and creates **test.exe** file in the root directory.

## Documentation

### Definitions

* **Value** - is a structure that is used as inputs and outputs of cells. It contains _input/output_ related data, e.g. floating point cell output.
* **Cell** - is a structure that has some (maybe zero) input and output values, and provides a way for manipulating these values.
* **Cluster** - is a structure containing multiple cells, and ruling these cells.
* **Producer** - is a structure that provides algorithms for managing and ruling clusters.

Current engine provides **nerone** namespace where all the *classes*, *types* and *functions* are defined.

___
### Types and aliases

* **nerone::shared_value_t** - alias for **std::shared_ptr\<nerone::value::Value\>**
* **nerone::shared_cell_t** - alias for **std::shared_ptr\<nerone::cell::Cell\>**
* **nerone::value_list_t** - alias for **std::vector\<nerone::shared_value_t\>**
* **nerone::cell_list_t** - alias for **std::vector\<nerone::shared_cell_t\>**
* **nerone::act_fn_t** - alias for *template\<typename FT\>* **std::function<FT(FT)>**
* **nerone::loss_fn_t** - alias for *template\<typename FT\>* **std::function<FT(FT,FT)>**
* **nerone::shared_train_data_t** - alias for **std::shared_ptr\<nerone::TrainData\>**
* **nerone::shared_cell_command_t** - alias for **std::shared_ptr\<CellCommand\>**
___

### class nerone::value::Value
Basic ***abstract*** *value* class with default constructor and default *virtual* destructor.

It doesn't provide any other functions or properties.
___

### class nerone::value::FValue\<T\>
***Abstract*** *value* class that extends **nerone::value::Value** with default constructor and destructor and provides 2 *pure virtual* methods and public type **f_type** = **T**.

Main purpose of this abstraction is to define a value floating point type, and provide *get/set* value interface.

#### virtual T get() = 0
Pure virtual method for getting the floating point value.

#### virtual void set(T value) = 0
Pure virtual method for setting the floating point value.
___

### class nerone::value::GValue\<T\>
***Abstract*** *value* class that extends **nerone::value::FValue\<T\>** with default constructor/destructor. It provides additional 2 *pure virtual* methods.

Main purpose of this abstraction is to provide *get_grad/set_grad* interface for manipulation value's gradient floaing point values.

#### virtual T get_grad() = 0
Pure virtual method for getting the floating point gradient value.

#### virtual void set_grad(T value) = 0
Pure virtual method for setting the floating point gradient value.
___

### class nerone::value::Cumulative\<T\>
Cumulative value class. It extends **nerone::value::GValue** It defines public **f_type** = **T** type.

This value class uses a stack for storing it's values.

It implements all pure virtual methods, and adds a couple of more methods for manipulating the memorty of the value.

#### T get()
Returns the last value from the stack.

#### void set(T value)
Sets the new value to be on top of the value stack.

#### get_grad()
Returns the grad value.

#### set_grad(T value)
Sets the grad value, and pops the most recently set *primary* value from the stack.

#### virtual void pop()
Removes the top value from the stack.

#### virtual void clean()
Cleans up the stack.

#### virtual bool empty()
Returns true if the value stack is empty.

***Examples:***
```c++
auto val = std::make_shared<nerone::value::Cumulative<float>>();
val->set(0.1);
val->get(); // 0.1
val->set(0.2);
val->get(); // 0.2
val->set_grad(0.5);
val->get(); // 0.1, as set_grad method removes the top value.
val->set_grad(0.6);
val->get(); // 0.1, the stack is empty, but the value is still remembered unless its overwritten by new `set()` call.
```

***Note:*** for examples on how it all works together, please reach to the *Cumulative* value tests. 
___

### nerone::cell::Cell
Basic ***abstract*** *cell* class with default constructor and default *virtual* destructor.

It also defines **4** pure virtual methods:

#### virtual const value_list_t& get_inputs() = 0
Returns the list of input value.

#### virtual const value_list_t& get_outputs() = 0
Returns the list of output values.

#### virtual void set_inputs(value_list_t vals) = 0
Assigns input values.

#### virtual void set_outputs(value_list_t vals) = 0
Assigns output values.
___

### nerone::cell::VCell\<VT\>
**Abstract** *template* class that extents **nerone::cell::Cell** with default constructor, and defines a single public **value_type** = **VT**.

The main purpose of this class is to define the *value* type that is used with the cell.

***Note:*** each class that extends **nerone::cell::VCell** class should define public **value_type**.
___

### nerone::cell::OCell\<VT\>
**Abstract** *Operationl* class that extends **nerone::cell::VCell\<VT\>** and additionally defines next pure abstract methods:

***Note:*** this cell accepts **VT** type that extends **nerone::value::Cumulative**.

#### virtual void calc_value() = 0
The method should calculate and *set* the cells **output** primary values.

#### virtual void calc_grad() = 0
The method should calculate and *set* the cells **input** gradient values.

#### virtual void clean() = 0
Cleans up *values*.

#### virtual void command(shared_cell_command_t command)
Allows sending additional *operational* signals to cells. Can be overwritten and special meaning set for specific *command*.

By default the function doesn't do anything whatever command is sent.

#### virtual void start()
Prepares the values or any other data for *calc* methods to be called. It doesn't  do anything fir this specific class, but can be overwritten and the *start* meaning defined.

#### void finish()
Cleaups the values or any other data. Basically it should return the cell into it's original state.
___

### nerone::cell::TCell\<VT\>
**Abstract** *trainable* class that provides trainable interface. It extends **nerone::cell::OCell\<VT\>**

It also defines public **weight_list_t** = **std::vector\<VT::f_type\>** type, and next trainable *pure virtual* methods:

#### virtual const weight_list_t& get_weights() = 0
Returns the list of weight floating values.

#### virtual void set_weights(weight_list_t weights) = 0
Assigns new weights to the current *trainable* cell.

#### virtual void update(shared_train_data_t data) = 0
Should update the weights with new floating values. It might take **data** sent as an argument into consideration. It may contain *learning rate* for example, etc.
___

### nerone::cell::Functional\<VT, FN\>
The **abstract** cell extends operational class (**nerone::cell::OCell\<VT\>**). It accepts 2 template parameters - **VT** is for *value* type, and **FN** is for *activation*/*gradient* function type. It has 1 *input* and 1 *output*, and provides a banch of constructors to fill in all of the internal states.

#### Functional()
Default constructor that assigns empty *input* and *output* values to the cell values, and assigns **nerone::activation::Linear** activation and gradients functions to the cell activation and gradient functions respectifully.

#### Functional(shared_value_t input, shared_value_t output)
Assigns *input* value and *output* value to the cells *input* and *output* values respectifully, assigns **linear** *activation* and *gradients* functions.

#### Functional(FN act, FN grad)
Assigns passed functions *act* and *grad* to the cells *activation* and *gradient* functions, and creates and assigns empty *input* and *output* values.

#### Functional(shared_value_t input, shared_value_t output, FN act, FN grad)
Assigns *input* and *output* to cells *input* and *output*, assigns *act* and *grad* to cells *activation* and *gradient* functions.

#### Functional(shared_value_t input, FN act, FN grad)
Like previous one, but only *input* value is assigned to cells *input* value, and *output* value is created assigned as empty value.

#### FN get_act_fn()
Returns *activation* function.

#### FN get_grad_fn()
Returns *gradient* function.

#### void set_act_fn(FN)
Assigns new *activation* function.

#### void set_grad_fn(FN)
Assigns new *gradient* function.

#### const value_list_t& get_inputs()
Returns the list of *inputs* with exactly one *input* value in it.

#### const value_list_t& get_outputs()
Returns the list of *outputs* with exactly one *output* value in it.

#### void set_inputs(value_list_t vals)
Sets up new *input* values. The list should contain only one *value*.

#### void set_outputs(value_list_t vals)
Sets up new *outputs* values. The list shlould contain only one *value*.

#### void set_input(shared_value_t value)
Sets up input value.

#### void set_output(shared_value_t value)
Sets up output value.

#### void clean()
Cleanups *input* and *output* *values*.
___

### nerone::cell::Activation\<VT\>
The class extends **nerone::cell::Functional\<VT, nerone::act_fn_t\<VT::f_type\>\>**. It accepts one template parameter *VT* - value type.

It inherits all parent class *constructors*, and implements the last 2 pure virtual methods:

#### void calc_value()
Applies *activation* function to the *input* value, and set the result to the *output* value.

#### void calc_grad()
Applies *gradient* function to the *output* gradient value, and set the result to the *input* gradient value.
___

### nerone::cell::Loss
The class extends **nerone::cell::Functional\<VT, nerone::loss_fn_t\<VT::f_type\>\>**. It accepts one template parameter *VT* - value type.

It inherits all parent class *constructors*, implements the last 2 pure virtual methods, and adds couple of more methods:

#### void calc_value(typename value_type::f_type expected)
Sets the *expected input* value to the passed *expected* floating value, and runs **void calc_value()**.

#### void calc_value()
Gets *calculated* value from its *input* value, and *expected* value from its *expected input* value, and uses them as inputs to its *loss activation* function. The result then assigned to the cells *output* value. This is basically the *error* value.

#### void calc_grad()
Gets *calculated* value from its *input* value, and *expected* value from its *expected input* value, and uses them as inputs to its *loss grad* function. The result then assigned to the cells *input* grad value.

#### void clean()
Cleans up *input*, *output* and *expected* values.

#### void set_expected_value(shared_value_t val)
Assigns *expected* input to the cell.

#### shared_value_t get_expected_value()
Returns currently assigned *expected* input.
___

### nerone::cell::Segment\<VT\>
The cell extends **nerone::cell::TCell\<VT\>** and implements all of the parents classes *abstract* methods.

It accepts one template parameter **VT** - value type.

The main purpose of this cell is to create, keep and manage *dense* connection *(weights)* between *input* and *input* values.

It also defines 3 public types:

* **value_type** = **VT**
* **weight_list_t** = **TCell\<VT\>::weight_list_t**
* **f_type** = **VT::f_type**

*There is default constructor exists.*

#### Segment(value_list_t inputs, value_list_t outputs)
Assigns passed *inuts* and *outputs* to cells *inputs* an *outputs* respectifully, and creates the matrix of *weights*.

#### const value_list_t& get_inputs()
Returns the list of *input* values.

#### const value_list_t& get_outputs()
Returns the list of *outputs* values.

#### void set_inputs(value_list_t vals)
Assigns new list of *input* values, and retuilds the *weights* matrix in case of the new input size is different from the old input size.

#### void set_outputs(value_list_t vals)
Same as above, but for output values.

#### void calc_value()
Calculates and sets *output* values floating values by the next formula:

Output[**i**] = SUM{**j** = [*0*, *INPUT_SIZE*]}(**Input[j]** * **weights\[i\]\[j\]**)

#### void calc_grad()
Calculates and sets *input* values floating gradient values.

#### void clean()
Cleanups *inputs* and *outputs* values and internal weights gradients.

***Note:*** weights are not cleaned by calling this method.

#### const weight_list_t& get_weights()
Returns the list of *weights*.

#### void set_weights(weight_list_t weights)
Assigns new list of weights to the cell.

***Note:*** the amount of weihts should be qual to **inputs.size()** * **outputs.size()**

#### void update(shared_train_data_t data)
Accepts **GDTrainData** smart pointer as an input, and uses it's **learning_rate** attribute to update the weights.

Note, each call to **calc_grad** cumulates the gradient for each weight, and when **update** function is called, its uses these cumulated values.

*That's how the **batch** size is simulated.
___

### nerone::cell::Cluster\<VT\>
**Abstract** class that extends **nerone::cell::TCell\<VT\>**. It accepts one template parameter **VT** - value type.

The main purpose of this cell is to keep and manage other cells. It doesn't really keep *weights* or it's own *inputs*, *ouput* or other values, so it inplements some of the *virtual* methods.

*It also has a default constructor*

***Note:*** all cells that cluster keeps must have *Operational* as one of their parents.


#### Cluster(cell_list_t cells)
Constructor that accepts the list of cells.

#### void update(shared_train_data_t data)
Basically just runs **update** method to all of its *Trainable* cells.

#### void calc_value()
Calls **calc_value** method for all of itscells. 

#### void calc_grad()
Calls **calc_grad** method for all of its cells.

#### void clean()
Calls **clean** method for all of its cells.

#### void start()
Calls **start** method for all of its cell.

#### void finish()
Calls **finish** method for all of its cells.

#### void command(shared_cell_command_t com)
Calls **command** method for all of its cells passing the same argument.

#### const weight_list_t& get_weights()
returns the empty list.

#### void set_weights(weight_list_t weights)
Doesn't really do anything.

#### virtual const cell_list_t& get_cells()
Returns the list of this cluster *cells*.

#### virtual void set_cells(cell_list_t cells)
Assigns new list of *cells* to the cluster.
___

### nerone::cell::Layer\<VT\>
Cluster cell that extends **nerone::cell::Cluster\<VT\>** and keeps cells that needs to be executed in paralel, making its inputs to be all the inputs of all its cells, and its outputs to be all the outputs from all of its cells.

It accepts one template type **VT** - value type.

*Has default constructor.*

#### Layer(cell_list_t cells)
Constructor that accepts and assigns cells that cluster will keep.

#### const value_list_t& get_inputs()
returns the list of *inputs* of all its *cells*.

#### const value_list_t& get_outputs()
returns the list of *outputs* of all its *cells*.

#### void set_inputs(value_list_t vals)
Assigns new *input* values to all of its *cells*.

#### void set_outputs(value_list_t vals)
Assigns new *output* values to all of its *cells*.
___

### nerone::cell::Sequense\<VT\>
Cluster cell that extends **nerone::cell::Cluster\<VT\>**. It has one template type **VT** - value type.

The porpose of this cell is to collect other operational cells, and apply methods to them in a sequentional manner.

*Default constructable.*

#### Sequence(cell_list_t cells)
Constructor that accepts and assigns cells that cluster will keep.

#### const value_list_t& get_inputs()
Returns its **first** cells *inputs*.

#### const value_list_t& get_outputs()
Returns its **last** cells *outputs*.

#### void set_inputs(value_list_t vals)
Assigns *value* lists to its **first** cell *inputs*.

#### void set_outputs(value_list_t vals)
Assigns *value* list to its **last** cell *outputs*.

#### void connect_cells()
Automatically connects all its cells *inputs* to *outputs*.
Basically it assigns each cell *outputs* to next cell *inputs*.
___

### nerone::cell::LossLayer\<VT\>
The sequense cell that extends **nerone::cell::Layer\<VT\>**, **nerone::cell::LossClusterInterface**.

The porpose of this cell is to collect other operational cells, and apply them in a sequentional manner.

#### LossLayer(cell_list_t cells)
Constructor that accepts the list of *cells*.

#### const value_list_t& get_expected_inputs()
returns the list of expected *inputs* from all of the *cells*.

#### void set_expected_inputs(value_list_t vals)
Accepts the list of *values* and assigns them to expected  values on each *cell*.
___

### nerone::Producer\<VT\>
Class that conducts all of the procesess related to training the neural network, and executing queries.

Each producer contain one **body** and one **loss** cells to operate with.

It defines 2 public types:
* **body_cell_t** = **std::shared_ptr\<cell::Cluster\<VT\>\>**
* **loss_cell_t** = **std::shared_ptr\<cell::LossLayer\<VT\>\>**

It has *default* constructor and *default virtual* destructor.

#### Producer(body_cell_t body, loss_cell_t loss)
Constructor that accepts **body** cell and **loss** *cells*.

#### virtual void set_body_cell(body_cell_t body)
Assigns **body** *cell*.

#### virtual void set_loss_cell(loss_cell_t loss) 
Assigns **loss** *cell*.

#### virtual body_cell_t get_body_cell()
Returns its **body** *cell*.

#### virtual loss_cell_t get_loss_cell()
Returns its **loss** *cell*.
___

### nerone::GDProducer

___

### Activation functions
There is a namespace **nerone::activation** with a bunch of activation functions already defined. Each of them consist of a class with 2 *public* *static* members **fun** and **grad** - *activation function* itself and a *derivative* of the activation function.

Each member is a template function with one template paraneter **T**  that requires *floating point* type to be passed. It accepts one argument with type `T`, and returns `T`.

**fun** function returns the result of applying activation function to the passed value.
**grad** function returns the result of applying gradient function to the passed value.

All activation functions described below live under the **nerone::activation** namespace.
___

### class nerone::activation::Sigmoid
The sigmoid function is a logistic function, which means that, whatever you input, you get an output ranging between 0 and 1.

### class nerone::activation::ReLU\<R\>
Parametric Reflicter activation function. For values less than 0, the result equals to value param. For values greater than 0, the result doesn't change. *R* should implement **std::ratio** class.
___

***Example:***
```c++
// Define class with parameter = 1/10 = 0.1
using ReLU01 = nerone::activations::ReLU<std::ratio<1,10>>

ReLU01::fun<float>(-10.0) // 1
ReLU01::fun<float>(15.0) // 15
```
___

### class nerone::activation::TanH
The output of the tanh activation function is Zero centered; hence we can easily map the output values as strongly negative, neutral, or strongly positive. Usually used in hidden layers of a neural network.
___

### class nerone::activation::ELU
Parametric Exponential Linear Unit activation function. For values less than 0, the result goes to -1 softly. Parameter decides the curve line for negative values. For values greater than 0, the result doesn't change. *R* should implement **std::ratio** class.
___

### class nerone::activation::GELU
Gaussian Error Linear Unit activation function. For values much less than 0, the result equals 0, but for values slightly less than 0, the result slightly less than 0. For values greater than 0 the result doesn't change.
___

### class nerone::activation::SELU
Scaled Exponential Linear Unit. This activation functions is one of the newer one's.
___

### class nerone::activation::Swish
Swish is a smooth, non-monotonic function that consistently matches or outperforms *ReLU* on deep networks applied to a variety of challenging domains such as Image classification and Machine translation.
___

### Loss functions
There is a **nerone::loss** namespace with **2** loss functions already defined. Each of them consist of a class with 2 *public* *static* members **fun** and **grad** - *activation function* itself and a *derivative* of the activation function.

Each member is a template function with one template paraneter **T**  that requires *floating point* type to be passed. It accepts two argument with type `T` _(actual value, and expected value)_, and returns `T`.

**fun** function returns the result of applying loss function to the passed values.
**grad** function returns the result of applying gradient loss function to the passed values.

All loss functions described below live under the **nerone::loss** namespace.
___

### class nerone::loss::MeanSquareError
Mean squared error (MSE) is the most commonly used loss function for regression. The loss is the mean overseen data of the squared differences between true and predicted values.
___

### class nerone::loss::CrossEntropy
Cross-entropy loss, or log loss, measures the performance of a classification model whose output is a probability value between 0 and 1. Cross-entropy loss increases as the predicted probability diverges from the actual label.

## Usage example

There is a **ner_one.h** file that includes all other *nerone* header files.

```c++
#include <iostream>
#include <memory>
#include <cstdlib>

#include "ner_one.h"
#include "src/build_helpers.cpp"

using ExecutionCase = nerone::GDProducer<nerone::value::Cumulative<float>>::ExecutionCase;
using ExecutionResult = nerone::GDProducer<nerone::value::Cumulative<float>>::ExecutionResult;

const double PI = 3.1415;

float rand_double() {
	return (rand()%10000)/(float)10000;
}

// Structure defining point on a plane, and bool parameter defining
// if the point belongs to red team or to blue team (true and false)
struct Point {
	double x;
	double y;
	bool red;
};

// Creates set of points devided for 2 sections, and puts red points
// to the top-right area of the plane, and blue points to the
// bottom-right are of the plane.
std::vector<Point> create_labeled_inputs_zones_2() {
	std::vector<Point> res;
	
	// top-right zone
	for(int i=0;i<100;i++){
		double len = rand_double() * 15;
		double a = rand_double() * PI * 2;
		res.push_back({len * std::sin(a) + 65, len * std::cos(a) + 35, true});
	}
	
	// bottom-left zone
	for(int i=0;i<100;i++){
		double len = rand_double() * 15;
		double a = rand_double() * PI * 2;
		res.push_back({len * std::sin(a) + 35, len * std::cos(a) + 65, false});
	}
	
	return res;
}

// Normalize the data
float norm(float a) {
	return a / 100 * 2 - 1;
}

void print_tests_result(std::vector<ExecutionCase> tests, std::vector<ExecutionResult> res) {
	for(int i=0;i<(int)tests.size();i++) {
		std::cout << tests[i].values[0] << " " << tests[i].values[1] << " " << res[i].values[0] << " " << res[i].values[1] << std::endl;
	}
}

int main() {
	srand(12345);

	// Creates a producer.
	auto *gd = new nerone::GDProducer<nerone::value::Cumulative<float>>();
	
	std::vector<int> layers{2, 6, 6, 2};
	
	// Prepares the weights matrix initial values.
	std::vector<std::vector<float>> weights;
	for(int i=1;i<(int)layers.size();i++) {
		int cnt = (layers[i-1]+1) * layers[i];
		std::vector<float> layer;
		for(int j=0;j<cnt;j++) {
			layer.push_back(rand_double());
		}
		weights.push_back(layer);
	}
	
	// Builds the cluster.
	ConnectedLayerBuilder b(true);
	b.add(layers[0], nerone::activation::Linear::fun<float>, nerone::activation::Linear::grad<float>);
	for(int i=1;i<(int)layers.size();i++) {
		b.add(layers[i], nerone::activation::Sigmoid::fun<float>, nerone::activation::Sigmoid::grad<float>);
	}
	b.withLoss(nerone::loss::CrossEntropy::fun<float>, nerone::loss::CrossEntropy::grad<float>);
	b.withWeights(weights);
	auto [body, loss] = b.build();

	// Assigns the cells.
	gd->set_body_cell(body);
	gd->set_loss_cell(loss);
	
	// Configure the producer.
	gd->set_learning_rate(0.01);
	gd->set_batch_size(1);
	gd->set_randomized(true);
	
	auto points = create_labeled_inputs_zones_2();
	std::vector<ExecutionCase> cases;
	for(auto &p : points) {
		cases.push_back({{norm(p.x), norm(p.y)}, {p.red ? 1.0f : 0.0f, p.red ? 0.0f : 1.0f}});
	}

	// Trains on labeld data.
	for(int i=0;i<100;i++) {
		gd->train(cases);
	}
	
	std::vector<ExecutionCase> tests;
	for(int i=0;i<100;i++) {
		for(int j=0;j<100;j++) {
			tests.push_back({
				{norm(j), norm(i)},
				{}
			});
		}
	}
	
	// Executes test data.
	auto res = gd->execute(tests);
	
	// print_tests_result(tests, res);
	
	return 0;
}
```

## Tests

Regular unit tests are placed under the **tests** folder.

Using the example I build above, with logging of additional useful data such as error function, and tests results I've been able to train neural network for different classification problems:

### 2 Zones problem (from the example in previous section)

* training step: **20** | error: **0.470739** 

  ![20 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_2_step_20.png?raw=true)
* training step: **40** | error: **0.0616046**

  ![40 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_2_step_40.png?raw=true)
* training step: **80** | error: **0.0130729**

  ![80 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_2_step_80.png?raw=true)
* training step: **100** | error: **0.00906824**

  ![100 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_2_step_100.png?raw=true)

### 4 Zones problem

* training step: **30** | error: **0.626602**

  ![30 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_4_step_30.png?raw=true)
* training step: **120** | error: **0.114609**

  ![120 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_4_step_120.png?raw=true)
* training step: **240** | error: **0.029581**

  ![240 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_4_step_240.png?raw=true)
* training step: **300** | error: **0.0197742**

  ![300 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/zones_4_step_300.png?raw=true)

### Circle problem

* training step: **80** | error: **0.678708**

  ![80 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/circle_step_80.png?raw=true)
* training step: **160** | error: **0.617172**

  ![160 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/circle_step_160.png?raw=true)
* training step: **280** | error: **0.371635**

  ![280 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/circle_step_280.png?raw=true)
* training step: **400** | error: **0.0287993**

  ![400 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/circle_step_400.png?raw=true)

### Spiral problem

* training step: **1000** | error: **0.662982**

  ![1000 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/spiral_step_1000.png?raw=true)
* training step: **4000** | error: **0.479241**

  ![4000 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/spiral_step_4000.png?raw=true)
* training step: **7000** | error: **0.133034**

  ![7000 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/spiral_step_7000.png?raw=true)
* training step: **10000** | error: **0.0362706**

  ![10000 steps](https://github.com/Immortale-dev/nerone/blob/master/res/imgs/nn_class_results/spiral_step_10000.png?raw=true)

As we can see, the neural network is able to be trained to solve these classification problems.

## Additional information

This project is a **low level** neural network engine. It is not a complete neural network framework you can use for real world tasks. To be so, additional wrapper required to be built on top of this engine providing methods to easier build of neural network, and even more important, reliable **GPU optimized cells** needs to be implemented to improve neural network training performance.

## License
MIT

Have fun :)
