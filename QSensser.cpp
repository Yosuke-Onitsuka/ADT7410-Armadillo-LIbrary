#include "QSensser.h"
#include <QDebug>

void QADT7410::mySig(uint16_t tmp){}
QADT7410::QADT7410(uint8_t Qaddr, unsigned char Qbus):ADT7410(Qaddr,Qbus){}
void QADT7410::qGetTmp(){
	tmp = getTmp();
	emit mySig(tmp);
}
