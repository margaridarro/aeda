#include "packagingMachine.h"
#include <sstream>

PackagingMachine::PackagingMachine(int boxCap): boxCapacity(boxCap)
{}

unsigned PackagingMachine::numberOfBoxes() {
    return boxes.size();
}

unsigned PackagingMachine::addBox(Box& b1) {
    boxes.push(b1);
    return boxes.size();
}

HeapObj PackagingMachine::getObjects() const {
    return this->objects;
}

HeapBox PackagingMachine::getBoxes() const {
    return this->boxes;
}


unsigned PackagingMachine::loadObjects(vector<Object> &objs) {
    auto it = objs.begin();

    while(it != objs.end()) {
        if (it->getWeight() <= boxCapacity) {
            objects.push(*it);
            it = objs.erase(it);
        }
        else it++;
    }
	return objects.size();
}

Box PackagingMachine::searchBox(Object& obj) {
    queue<Box> aux;

    while(!boxes.empty()){
        Box b = boxes.top();
        boxes.pop();
        if(b.getFree() >= obj.getWeight()){
            while(!aux.empty())
            {
                boxes.push(aux.front());
                aux.pop();
            }
            return b;
        }
        aux.push(b);
    }
    while(!aux.empty())
    {
        boxes.push(aux.front());
        aux.pop();
    }

	return Box(boxCapacity);
}


unsigned PackagingMachine::packObjects() {

	while (!objects.empty())
	{
	    Object o = objects.top();
        objects.pop();
        Box b = searchBox(o);
        b.addObject(o);
        boxes.push(b);
	}
	return boxes.size();
}


string PackagingMachine::printObjectsNotPacked() const {
    stringstream ss;
    if( objects.empty() ) ss << "No objects!" << endl;
    else {
        HeapObj buffer = objects;
        while( !buffer.empty() ) {
            Object obj = buffer.top();
            buffer.pop();
            ss << obj << endl;
        }
    }
    return ss.str();
}


Box PackagingMachine::boxWithMoreObjects() const {
    if( boxes.empty() ) throw MachineWithoutBoxes();
    else {
        HeapBox buffer = boxes;
        Box boxMore = buffer.top();
        buffer.pop();
        while( !buffer.empty() ) {
            if( boxMore.getSize() < buffer.top().getSize() )
                boxMore = buffer.top();
            buffer.pop();
        }
        return boxMore;
    }
}