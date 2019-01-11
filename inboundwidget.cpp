#include "const.h"
#include "inboundwidget.h"
#include "ui_inboundwidget.h"

InboundWidget::InboundWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InboundWidget),
    qry(new QSqlQuery),
    modelInbound(new QSqlQueryModel),
    modelCategory(new QSqlQueryModel)
{
    qDebug() << "[Inbound Widget] Constructing...";
    ui->setupUi(this);
    ui->lineEditNameKey->setMaxLength(ITEMNAME_MAX_LEN);

    // TODO: connect [InventoryWidget::pushButtonInbound] and
    // this refreshCategoryComboBox()

    refreshInboundTableView();
    refreshCategoryComboBox();
}

InboundWidget::~InboundWidget()
{
    qDebug() << "[Inbound Widget] Destructing...";
    delete ui;
    delete qry;
    delete modelInbound;
    delete modelCategory;
}

void InboundWidget::on_pushButtonQuery_clicked()
{
    qDebug() << "[Inbound Widget] Query button clicked...";
    QString nameKey = ui->lineEditNameKey->text();
    QString category = ui->comboBoxCategory->currentText();
    bool searchName = ui->checkBoxName->isChecked();
    bool categoryOnly = ui->checkBoxCate->isChecked();

    QString clause = "";  // Prepare query where cluase if needed.
    QString nameCondition = QString("name LIKE '%%1%'").arg(nameKey);
    QString cateCondition = QString("cate = '%1'").arg(category);
    if (searchName)
    {
        clause += " WHERE " + nameCondition;
        if (categoryOnly) clause += " AND " + cateCondition;
    }
    else if (categoryOnly) clause += " WHERE " + cateCondition;

    refreshInboundTableView(clause);
}

void InboundWidget::refreshInboundTableView(const QString& qry_clause)
{
    qDebug() << "Refreshing inbound table view...";
    QString s = "SELECT name AS %1, cate AS %2, time as %3 FROM Inbound";
    QString view_inbound = s.arg(
        tr("Name"), tr("Category"), tr("Time")) + qry_clause;
    qDebug() << view_inbound;
    modelInbound->setQuery(view_inbound);
    ui->tableViewInbound->setModel(modelInbound);
}

void InboundWidget::refreshCategoryComboBox()
{
    qDebug() << "Refreshing category combo box...";
    QString get_distinct_cate = "SELECT DISTINCT cate FROM Inbound";
    modelCategory->setQuery(get_distinct_cate);
    ui->comboBoxCategory->setModel(modelCategory);
}