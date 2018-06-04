#include "ADT7410.h"
#include <QApplication>

class QADT7410 : public ADT7410, public QObject{
	public :
	uint16_t tmp;

	QADT7410(uint8_t Qaddr, unsigned char Qbus);
	void qGetTmp();

	signals:
	void mySig(uint16_t tmp);
};
