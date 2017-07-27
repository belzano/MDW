##DISCLAIMER

Purposes of that repo:
* This is my playground: 
 * code snippets, 
 * tests of technical features 
 * attempts of new patterns. 
* Ability to quickly setup/start a new C++ application by providing common "blocks".

None of the code in that repository was ever run on production. 

##CONTENTS

### UHF (Standing for Ultimate Hosting Framework) is a modular application execution framework.
UHF allows definition of reusable code blocks (aka "components"): Updaters and Updatable, Listeners (Queue, Event, networks) and consumers, etc.
An application behaviour can then be quickly defined, by specifying its components and interactions as a json file.

some .json bootstrap files are availables in etc/ 
bin/uhf_bin -b ~/MDW/etc/bootstrap.json

Coming next:
* Refactoring existing components as Entity / Rewrite boostrap decoding accordingly 
* Rewrite HttpService invocator. Update Invocation Request so it can handle sync/async
* Fix monitoring services (and migrate them to instructions/events)
* Forking abilitites in bootstrap, eg ability to define a cluster (agent, front-end, back-ends)
* Bus communication between processes through named queues (Sending events/instructions)
* Update Tasks framework
* Round robin fanout/dispatcher

### MME is the business logic for an image vectorisation engine. 
It analyses whiteboard pictures during meetings and produces a clean, vectorized output (as svg) to embed in meeting minutes.


### toolbox is a common utility library with generic helpers / OS wrappers etc.


##INSTALLATION

Some dependencies are required:
* cmake, g++
* libs open-cv: libopencv-highgui-dev libopencv-features2d-dev
* libs boost: libboost-dev libboost-filesystem-dev 
* libs microhttpd: libmicrohttpd-dev 



