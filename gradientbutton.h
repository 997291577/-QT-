#pragma execution_character_set("utf-8")

#ifndef GRADIENTBUTTON_H
#define GRADIENTBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QMouseEvent>
#include <QPainter>
#include <QIcon>

class GradientButton : public QPushButton {
    Q_OBJECT

    /////////////*定义属性，可从ui界面中修改*//////////////////
    //当前颜色
    Q_PROPERTY(QColor gradientColor READ getGradientColor WRITE setGradientColor NOTIFY gradientColorChanged);
    //平时颜色
    Q_PROPERTY(QColor normalColor READ getNormalColor WRITE setNormalColor NOTIFY normalColorChanged);
    //鼠标悬浮颜色
    Q_PROPERTY(QColor hoverColor READ getHoverColor WRITE setHoverColor NOTIFY hoverColorChanged);
    //鼠标按下颜色
    Q_PROPERTY(QColor clickedColor READ getClickedColor WRITE setClickedColor NOTIFY clickedColorChanged);
	//文本颜色
	Q_PROPERTY(QColor textColor READ getTextColor WRITE setTextColor NOTIFY textColorChanged);
	//按钮圆角半径
	Q_PROPERTY(int cornerRadius READ getCornerRadius WRITE setCornerRadius NOTIFY cornerRadiusChanged);
	//按钮文本
	Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged);
	//icon图标路径
	Q_PROPERTY(QString iconPath READ getIconPath WRITE setIconPath NOTIFY iconPathChanged);
	//渐变时间
	Q_PROPERTY(int gradientTime READ getGradientTime WRITE setGradientTime NOTIFY gradientTimeChanged);
	//Icon的x坐标
	Q_PROPERTY(int iconX READ getIconX WRITE setIconX NOTIFY iconXChanged);
public:
    GradientButton(QWidget* parent = nullptr);

    //获取颜色
    QColor getGradientColor() const;
    QColor getNormalColor() const;
    QColor getHoverColor() const;
    QColor getClickedColor() const;
	QColor getTextColor() const;
	//获取圆角半径
	int getCornerRadius() const;
	//获取渐变时间
	int getGradientTime() const;
	//获取文本
	QString getText() const;
	//获取icon图标路径
	QString getIconPath() const;
	//获取Icon的x坐标
	int getIconX() const;
public slots:
    //设置颜色
    void setGradientColor(const QColor& color);
    void setNormalColor(const QColor& normalColor);
    void setHoverColor(const QColor& hoverColor);
    void setClickedColor(const QColor& clickedColor);
	void setTextColor(const QColor& textColor);
	//设置按钮圆角半径
	void setCornerRadius(int cornerRadius);
	//设置文本
	void setText(QString cornerRadius);
	//设置渐变时间
	void setGradientTime(int gradientTime);
	//设置icon图标路径
	void setIconPath(QString iconPath);
	//设置Icon的x坐标
	void setIconX(int iconX);
signals:
    //改变信号
    void gradientColorChanged(QColor newColor);
    void normalColorChanged(QColor normalColor);
    void hoverColorChanged(QColor hoverColor);
    void clickedColorChanged(QColor clickedColor);
	void textColorChanged(QColor clickedColor);
	void cornerRadiusChanged(int cornerRadius);
	void textChanged(QString text);
	void iconPathChanged(QString iconPath);
	void gradientTimeChanged(int time);
	void iconXChanged(int iconX);
protected:
    //各种事件
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEvent* event) override;
    void leaveEvent(QEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;

private slots:
    //鼠标按下槽函数
    void onPressed();
    //鼠标松开槽函数
    void onReleased();

private:
    //控制颜色渐变
    void animateToColor(const QColor& targetColor);

    QPropertyAnimation* animation;  //控制颜色渐变
    QColor m_normalColor;           //平时颜色
    QColor m_hoverColor;            //鼠标悬浮颜色
    QColor m_clickedColor;          //鼠标按下颜色
    QColor m_gradientColor;        //当前颜色
	QColor m_textColor;				//文本颜色

	QString m_text;						//按钮文本
	QString m_iconPath;				//icon图标路径

	int		m_cornerRadius;			//按钮圆角半径
	int		m_gradientTime;			//渐变时间
	int		m_iconX;						//icon的X坐标
};

#endif // GRADIENTBUTTON_H
