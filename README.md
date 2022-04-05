# NerOne

Low level neural network **C++** engine. The engine provides a huge flexibility in creating neural networks. It also gives an ability for performance optimisations. Details in the [optimisation]() section of documentation.

## Table of Contest

## Build
Library was tested using **GNU G++** compiler with flag **-std=c++17**. So it is recommended to use C++ 17 or higher version of compiler. Compiling by other compilers may require code corrections.


## Documentation

### Definitions
* **Node** - Smallest piece of a neural network containing value of this node and a list of connections to previous nodes and can return some output value produced by some activation function.
* **Bias** - special node that belongs to layer, which value is not calculated, nor set as input, but always equals **1**. This node defines some shift that always added to the hidden and/or output nodes values. 
* **Layer** - is a list of nodes. Layer can be *input* - first layer of the neural network. Each node's value of the a first layer defined by input parameters. There is always 1 input layer in a neural network. *output layer* - is a the last layer of a neural network. Values of the nodes of an output layer are the results of the neural network calculations (propagation). *hidden layer* - is a layer in between input and output layers. There may be more than 1 hidden layer in the network. 
* **Activation function** - is a function applied to the node's value to the the node's output.
* **Loss function** - is a function applied to all the output node's outputs to calculate the error of the neural network.
* **Training neural network** - means adjusting the neural network node's connection weights to decrease the error.
* **Error of neural network** - value showing the accuracy of neural network result. The higher error - the less accurate neural network.

Current engine provides **nerone** namespace where all the *classes*, *types* and *functions* are defined.

### Types and aliases
* **value_t** - alias for **double** type.
* **value_list_t** - alias for **std::vector\<value_t\>** type.
* **shared_node_t** - alias for **std::shared_ptr\<NerNode\>** type.
* **shared_syn_t** - alias for **std::shared_ptr\<NerSyn\>** type.
* **shared_layer_t** - alias for **std::shared_ptr\<NerLayer\>** type.
* **shared_cluster_t** - alias for **std::shared_ptr\<NerCluster\>** type.
* **syn_list_t** - alias for **std::vector\<shared_syn_t\>**
* **node_list_t** - alias for **std::vector\<shared_node_t\>** type.
* **layer_list_t** - alias for **std::vector\<shared_layer_t\>** type.
* **act_fn_t** - alias for **std::function\<value_t(value_t)\>** type.

### class nerone::Node
Defines neural network **node**. Defines default copy and move constructors.

#### constructor(nerone::value_t value)
Creates instance of **Node** class, and defines *value* attribute of the node.

#### constructor(nerone::value_t value, nerone::act_fn_t act_fn)
Creates instance of **Node** class, and defines *value* and *act_fn* attributes of the node.

#### nerone::value_t get_value()
Returns node's value.

#### void set_value(value_t value)
Defines node's value property.

#### nerone::act_fn_t& get_act_fn()
Returns node's activation function.

#### void set_act_fn(act_fn_t fn)
Defines node's activation function.

#### nerone::syn_list_t& get_syns()
Returns list of connections to the previous layer (including **NerSyn** to the bias if exists)

#### void  set_syns(syn_list_t syns)
Defines list of connections to the previous layer of the neural network.

#### nerone::value_t  get_output()
Applies activation function to the node's *value* and returns the result.

### class nerone::NerGNode : public nerone::NerNode
Additionally declares methods to define and use gradient functions. Defines 

#### constructor(value_t val)
Creates instance of **NerGNode** class, and defines *value* property.

#### constructor(value_t val, act_fn_t act_fn, act_fn_t grad_fn)
Creates instance of **NerGNode** class and defines *value*, activation function and gradient function.

#### nerone::act_fn_t& get_gradient_fn()
Returns node's gradient function.

#### void  set_gradient_fn(act_fn_t fn)
Defines gradient function of the node.

#### nerone::value_t  get_gradient()
applies gradient function to the node's value, and returns the result.

### class nerone::NerSyn
Defines neural network connection between nodes from different neighbour layers (from current to previous layer). Class defines default copy and move constructors.

#### constructor(shared_node_t node, value_t weight)
Creates instance of **NerSyn** class and defines *node* and *weight* properties.

#### nerone::value_t  get_weight()
Returns syn's weight.

#### void set_weight(value_t weight)
Defines weight of the **NerSyn**

#### nerone::shared_node_t  get_node()
Returns smart pointer to the node from the previous layer connected to current **node**.

#### void  set_node(shared_node_t node)
Connects node from previous layer to current node. 

### class nerone::NerLayer
Defines neural network layer containing list of nodes included into the layer. Defines default copy and move constructors.

#### constructor(node_list_t nodes)
Creates instance of **NerLayer** class and defines list of layer's nodes.
***Note:*** node_list_t = vector\<std::shared_ptr\<NerNode\>\>

#### node_list_t& get_nodes()
Returns list of nodes of the current layer, or **nullptr** if it's not defined.

#### void  set_nodes(node_list_t nodes)
Defines layer's list of nodes.

#### size_t size()
returns the size of the layer's nodes list.

#### nerone::shared_node_t& operator\[\]\(size_t ind\)
Returns node from the list of nodes with index = **ind**.

#### nerone::shared_node_t& get_bias()
Returns layer's **bias** node or null if doesn't exist.

#### void  set_bias(shared_node_t bias)
Defines **bias** node of the layer.

### class nerone::NerCluster
Defines neural network structure. It collects all the layers but not defines any training or propagation algorithms. Defines default copy and move constructors.

#### constructor(layer_list_t layers)
Accepts list of layers, creates instance of NerCluster class, defines list of layers of neural network.

#### nerone::layer_list_t& get_layers()
Returns a list of layers of neural network.

#### void set_layers(layer_list_t layers)
Defines layers of neural network.

#### shared_layer_t& first_layer()
Returns first layer from neural network (input layer), or throws if there are no layers.

#### shared_layer_t& last_layer()
Returns last layer from neural network (output layer), or throws if there are no layers.

### class nerone::NerBox<M, T>
Constructor of the class accepts cluster and defines basic interface for propagation and back propagation algorithms as well as finding errors.

It accepts 2 template parameters: 
* **M** is multiplier class used by propagation method of the interface. 
* **T** is teacher class used by back propagation method of the interface.

#### constructor(shared_cluster_t cluster)
Creates instance of the class and defines cluster attribute.

#### nerone::shared_cluster_t get_cluster()
Returns cluster of the neural network.

#### void set_cluster(shared_cluster_t cluster)
Defines cluster of the neural network.

#### nerone::value_list_t question(value_list_t questions)
Checks that number of items in **questions** equals to a number of nodes in the first layer of *cluster*, and runs **M** (multiplier) class instance "()" operator function with **cluster** as the first parameter, and **questions** as the second parameter.

#### void correct(value_list_t answers)
Checks that numbers of items in **answers** equals to a number of nodes in the last layer of *cluster*, and runs **T** (teacher) class instance "()" operator function with **cluster** as the first parameter, and **answers** as the second parameter. 

Running this method requires values of cluster's nodes to be set by performing *question* method.

#### void teach(value_list_t questions, value_list_t answers)
Runs **question** and **correct** with corresponding parameters **questions** and **answers**.

#### M& get_multiplier()
Returns instance of **M** (multiplier) class. It allows you to set up any dynamic parameters you need before or between "asking questions".

#### T& get_teacher()
Returns instance of **T** (teacher) class. It allows you to set up any dynamic parameters you need before or between "trainings".

#### nerone::value_list_t get_errors(value_list_t expected)
Runs **T::get_errors** with **expected** as the first argument of the function, and returns the result. The resulting list contains error value for each output node.

Running this method requires values of cluster's nodes to be set by performing *question* method.

### Activation functions
There is a namespace **nerone::activations** with a bunch of activation functions already defined. Each of them consist of a class with 2 *public* *static* members **fun** and **grad** - *activation function* itself and a *derivative* of the activation function.

All activation functions described below live under the **nerone::activations** namespace.

***Usage example:***
```c++
auto* node = new nerone::NerGNode(0, nerone::activations::Sigmoid::fun, nerone::activations::Sigmoid::grad);
```

### class Sigmoid
The sigmoid function is a logistic function, which means that, whatever you input, you get an output ranging between 0 and 1.

### class ReLU\<R\>
Parametric Reflicter activation function. For values less than 0, the result equals to value param. For values greater than 0, the result doesn't change. *R* should implement **std::ratio** class.

***Example:***
```c++
// Define class with parameter = 1/10 = 0.1
using ReLU01 = nerone::activations::ReLU<std::ratio<1,10>>

ReLU01::fun(-10) // 1
ReLU01::fun(15) // 15
```

### class TanH
The output of the tanh activation function is Zero centered; hence we can easily map the output values as strongly negative, neutral, or strongly positive. Usually used in hidden layers of a neural network.

### class ELU
Parametric Exponential Linear Unit activation function. For values less than 0, the result goes to -1 softly. Parameter decides the curve line for negative values. For values greater than 0, the result doesn't change. *R* should implement **std::ratio** class.

### class GELU
Gaussian Error Linear Unit activation function. For values much less than 0, the result equals 0, but for values slightly less than 0, the result slightly less than 0. For values greater than 0 the result doesn't change.

### class SELU
Scaled Exponential Linear Unit. This activation functions is one of the newer one's.

### class Swish
Swish is a smooth, non-monotonic function that consistently matches or outperforms *ReLU* on deep networks applied to a variety of challenging domains such as Image classification and Machine translation.

### Loss functions
There is a **nerone::loss** namespace with **2** loss functions already defined. Each of them consist of a class with 2 *public* *static* members **fun** and **grad** - *activation function* itself and a *derivative* of the activation function.

All loss functions described below live under the **nerone::loss** namespace.

### class MeanSquareError
Mean squared error (MSE) is the most commonly used loss function for regression. The loss is the mean overseen data of the squared differences between true and predicted values.

### class CrossEntropy
Cross-entropy loss, or log loss, measures the performance of a classification model whose output is a probability value between 0 and 1. Cross-entropy loss increases as the predicted probability diverges from the actual label.

### Multipliers
There is a **nerone::multipliers** namespace defining multiplier classes.
Each such class should implement **()** operator function accepting **shared_cluster_t& cluster** as the first argument, and **value_list_t&& values** as the second argument, and should propagate values through the layers of the **cluster**.

There is one multiplier class already defined under **nerone::multipliers** namespace.

### BaseMultiplier\<O\>
Class implements neuron network propagation algorithm. Accepts template parameter O that allow to provide multiplication optimisations. **O** class should implement **nerone::BaseCalculator** interface.

By default **nerone::BaseCalculator** used as a template parameter.

### Teachers
There is a **nerone::teachers** namespace defining teachers classes.
Each such class should implement **()** operator function accepting **shared_cluster_t& cluster** as the first argument, and **value_list_t&& values** as the second argument, and should back propagate values through the layers of the **cluster** adjusting weights of the **syns** to reduce the *error* of the neural network.

Each teacher class *must* also implement **get_errors** function returning **value_list_t**, and accepting **shared_cluster_t& cluster** as the first argument, and **value_list_t expected** as the second argument.
This function should calculate error of each output node and return this list of errors.

There is one teacher class already defined under **nerone::teachers** namespace.

### GradientDescent<N, L, O>
Class implements the most common **Gradient Descent** neural network back propagation algorithm. It accepts **3** template parameters:
* **N** corresponds to the *Node* type used in the neural network. **N** should extend **NerNode** class and additionally it should implement **get_gradient** method returning gradient of the *value* node's property.
	There is **NerGNode** already defined that meets this requirement.
* **L** corresponds to the *loss function* type. See the [section]() above.
* **O** corresponds to the *optimisation* class. It should implement **nerone::BaseCalculator** interface.
	By default **nerone::BaseCalculator** class used as **O** template parameter.

***Example:***
```c++
auto cluster = generate_cluster(); // generates cluster, lol
auto box = new nerone::NerBox<nerone::multipliers::BaseMultiplier<>, nerone::teachers::GradientDescent<nerone::NerGNode, nerone::loss::MeanSquareErrors>>(cluster);
```

### BaseCalculator


## Usage example


## Tests


## Additional information


## License
MIT

Have fun :)
