#ifndef QSEARCHBAR_H
#define QSEARCHBAR_H

#include <QLineEdit>
#include <QPropertyAnimation>

class QSearchBar : public QLineEdit
{
    Q_OBJECT
public:
    explicit QSearchBar(QWidget *parent = nullptr);

protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QToolButton *searchButton;
    QToolButton *clearButton;

    QPropertyAnimation *animationSearchButton;

    QFontMetrics *font;

private slots:
    void updateClearButton(const QString &text);
    void playAnimationSearchButton();
    void search();
    void clearText();

public slots:
    void setIconSearchButton(QIcon icon, QSize size);
    void setIconClearButton(QIcon icon, QSize size);

signals:
    void searchInfo();
    void haveFocus();
    void clearInfo();
};

#endif // QSEARCHBAR_H
