#include <string>
#include "stdlib.h"

#include "../includes/waiter.h"
#include "../includes/PRINT.h"
#include "../includes/externs.h"
using namespace std;

Waiter::Waiter(int id, std::string filename) :
		id(id), myIO(filename) {
}

Waiter::~Waiter() {
}

//gets next Order(s) from file_IO
int Waiter::getNext(ORDER &anOrder) {
	int next_order = myIO.getNext(anOrder);
	return next_order;
}

void Waiter::beWaiter() {
	ORDER anOrder;
	int next_order = getNext(anOrder);


	while (next_order == SUCCESS) { //fetch orders until no more orders

			PRINT5("\nWAITER: ", id, " Inserting Order ", anOrder.order_number, " into queue ");
			std::unique_lock<mutex> alock(mutex_order_outQ);
			order_in_Q.push(anOrder);

			next_order = getNext(anOrder);
			cv_order_inQ.notify_all();
		}
	b_WaiterIsFinished = true;
	cv_order_inQ.notify_all();
	}


