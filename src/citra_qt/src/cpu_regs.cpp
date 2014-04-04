#include "cpu_regs.hxx"

#include "core.h"
#include "arm/armdefs.h"

GARM11RegsView::GARM11RegsView(QWidget* parent) : QDockWidget(parent)
{
    cpu_regs_ui.setupUi(this);

    tree = cpu_regs_ui.treeWidget;
    tree->addTopLevelItem(registers = new QTreeWidgetItem(QStringList("Registers")));
    tree->addTopLevelItem(CSPR = new QTreeWidgetItem(QStringList("CSPR")));

    registers->setExpanded(true);
    CSPR->setExpanded(true);

    for (int i = 0; i < 16; ++i)
    {
        QTreeWidgetItem* child = new QTreeWidgetItem(QStringList(QString("R[%1]").arg(i, 2, 10, QLatin1Char('0'))));
        registers->addChild(child);
    }

    CSPR->addChild(new QTreeWidgetItem(QStringList("M")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("T")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("F")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("I")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("A")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("E")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("IT")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("GE")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("DNM")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("J")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("Q")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("V")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("C")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("Z")));
    CSPR->addChild(new QTreeWidgetItem(QStringList("N")));
}

void GARM11RegsView::OnCPUStepped()
{
    ARMul_State* state = Core::GetState();
    for (int i = 0; i < 16; ++i)
        registers->child(i)->setText(1, QString("0x%1").arg(state->Reg[i], 8, 16, QLatin1Char('0')));

    CSPR->setText(1, QString("0x%1").arg(state->Cpsr, 8, 16, QLatin1Char('0')));
    CSPR->child(0)->setText(1, QString("b%1").arg(state->Cpsr & 0x1F, 5, 2, QLatin1Char('0'))); // M - Mode
    CSPR->child(1)->setText(1, QString("%1").arg((state->Cpsr >> 5) & 0x1));	// T - State
    CSPR->child(2)->setText(1, QString("%1").arg((state->Cpsr >> 6) & 0x1));	// F - FIQ disable
    CSPR->child(3)->setText(1, QString("%1").arg((state->Cpsr >> 7) & 0x1));	// I - IRQ disable
    CSPR->child(4)->setText(1, QString("%1").arg((state->Cpsr >> 8) & 0x1));	// A - Imprecise abort
    CSPR->child(5)->setText(1, QString("%1").arg((state->Cpsr >> 9) & 0x1));	// E - Data endianess
    CSPR->child(6)->setText(1, QString("%1").arg((state->Cpsr >> 10) & 0x3F));	// IT - If-Then state (DNM)
    CSPR->child(7)->setText(1, QString("%1").arg((state->Cpsr >> 16) & 0xF));	// GE - Greater-than-or-Equal
    CSPR->child(8)->setText(1, QString("%1").arg((state->Cpsr >> 20) & 0xF));	// DNM - Do not modify
    CSPR->child(9)->setText(1, QString("%1").arg((state->Cpsr >> 24) & 0x1));	// J - Java state
    CSPR->child(10)->setText(1, QString("%1").arg((state->Cpsr >> 27) & 0x1));	// Q - Sticky overflow
    CSPR->child(11)->setText(1, QString("%1").arg((state->Cpsr >> 28) & 0x1));	// V - Overflow
    CSPR->child(12)->setText(1, QString("%1").arg((state->Cpsr >> 29) & 0x1));	// C - Carry/Borrow/Extend
    CSPR->child(13)->setText(1, QString("%1").arg((state->Cpsr >> 30) & 0x1));	// Z - Zero
    CSPR->child(14)->setText(1, QString("%1").arg((state->Cpsr >> 31) & 0x1));	// N - Negative/Less than
}
