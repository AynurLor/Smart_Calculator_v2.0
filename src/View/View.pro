QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Model/Credit_calc.cpp \
    ../Model/Deposit_calc.cpp \
    ../Model/Stack.cpp \
    ../Model/Valid.cpp \
    ../Model/s21_Model.cpp \
    calculator.cpp \
    credit.cpp \
    deposit.cpp \
    main.cpp \
    View.cpp \
    qcustomplot.cpp

HEADERS += \
    ../Contreller/Controller.hpp \
    ../Model/s21_Model.hpp \
    View.h \
    calculator.h \
    credit.h \
    deposit.h \
    qcustomplot.h

FORMS += \
    View.ui \
    calculator.ui \
    credit.ui \
    deposit.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += \
	resurse.qrc

DISTFILES += \
	Game_Button_Elements (7).png \
	Game_Button_Elements (7).png
