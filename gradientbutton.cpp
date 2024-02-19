#include "gradientbutton.h"

GradientButton::GradientButton(QWidget* parent)
    : QPushButton(parent), animation(new QPropertyAnimation(this, "gradientColor")),
      m_normalColor(QColor(22, 64, 214)),
      m_hoverColor(QColor(59, 101, 227)),
      m_clickedColor(QColor(9, 39, 176)),
      m_gradientColor(m_normalColor),
	  m_cornerRadius(0),
	  m_textColor(QColor(255, 255, 255)),
	  m_iconPath(QString("")),
	  m_gradientTime(200),
	  m_iconX(20)
{
	//设置渐变时间
    animation->setDuration(m_gradientTime);

	//设置按钮按下与弹起槽函数
    connect(this, &GradientButton::pressed, this, &GradientButton::onPressed);
    connect(this, &GradientButton::released, this, &GradientButton::onReleased);
}

//获取当前颜色
QColor GradientButton::getGradientColor() const
{
    return m_gradientColor;
}

//获取平时颜色
QColor GradientButton::getNormalColor() const
{
    return m_normalColor;
}

//获取鼠标悬浮颜色
QColor GradientButton::getHoverColor() const
{
    return m_hoverColor;
}

//获取鼠标按下颜色
QColor GradientButton::getClickedColor() const
{
    return m_clickedColor;
}

QColor GradientButton::getTextColor() const
{
	return m_textColor;
}

int GradientButton::getCornerRadius() const
{
	return m_cornerRadius;
}

int GradientButton::getGradientTime() const
{
	return m_gradientTime;
}

QString GradientButton::getText() const
{
	return m_text;
}

QString GradientButton::getIconPath() const
{
	return m_iconPath;
}

int GradientButton::getIconX() const
{
	return m_iconX;
}

//设置当前颜色
void GradientButton::setGradientColor(const QColor& color)
{
    m_gradientColor = color;
    update();
}

//设置平时颜色
void GradientButton::setNormalColor(const QColor& normalColor)
{
    if (m_normalColor == normalColor)
        return;

    m_normalColor = normalColor;
    update();
    emit normalColorChanged(m_normalColor);
}

//设置鼠标悬浮颜色
void GradientButton::setHoverColor(const QColor& hoverColor)
{
    if (m_hoverColor == hoverColor)
        return;

    m_hoverColor = hoverColor;
    update();
    emit hoverColorChanged(m_hoverColor);
}

//设置鼠标按下颜色
void GradientButton::setClickedColor(const QColor& clickedColor)
{
    if (m_clickedColor == clickedColor)
        return;

    m_clickedColor = clickedColor;
	update();
    emit clickedColorChanged(m_clickedColor);
}

void GradientButton::setTextColor(const QColor & textColor)
{
	if (m_textColor == textColor)
		return;

	m_textColor = textColor;
	update();
	emit textColorChanged(m_textColor);
}

void GradientButton::setCornerRadius(int cornerRadius)
{
	if (m_cornerRadius == cornerRadius)
		return;

	m_cornerRadius = cornerRadius;
	update();
	emit cornerRadiusChanged(m_cornerRadius);
}

void GradientButton::setText(QString text)
{
	if (m_text == text)
		return;

	m_text = text;
	update();
	emit textChanged(text);
}

void GradientButton::setGradientTime(int gradientTime)
{
	if (m_gradientTime == gradientTime)
		return;

	m_gradientTime = gradientTime;
	animation->setDuration(m_gradientTime);
	update();
	emit gradientTimeChanged(gradientTime);
}

void GradientButton::setIconPath(QString iconPath)
{
	if (m_iconPath == iconPath)
		return;

	m_iconPath = iconPath;
	update();
	emit iconPathChanged(m_iconPath);
}

void GradientButton::setIconX(int iconX)
{
	if (m_iconX == iconX)
		return;

	m_iconX = iconX;
	update();
	emit iconXChanged(m_iconX);
}

void GradientButton::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
	//QPushButton::paintEvent(event);//禁用QT按钮自带的绘制

	//启用绘制与文本抗锯齿
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
	//绘制按钮，需要设置无画笔，否则圆角不标准并且边框会是画笔的颜色
	painter.setPen(Qt::NoPen); 
	painter.setBrush(m_gradientColor);
    painter.drawRoundedRect(rect(), m_cornerRadius, m_cornerRadius);
	// 设置文本颜色
	painter.setPen(m_textColor);
	// 绘制文本
	painter.drawText(this->rect(), Qt::AlignCenter, m_text);
	//绘制图标
	QFile file(m_iconPath);
	// 图标存在
	if (file.exists()) 
	{
		QPixmap originalPixmap(m_iconPath);
		//图标默认垂直居中，计算y坐标
		int iconY = (this->height() - originalPixmap.height()) / 2;
		painter.drawPixmap(m_iconX, iconY, originalPixmap);
	}

}

void GradientButton::enterEvent(QEvent* event)
{
    QPushButton::enterEvent(event);
	if (!this->isChecked())
	{
		animateToColor(m_hoverColor);
	}
    
}

void GradientButton::leaveEvent(QEvent* event)
{
    QPushButton::leaveEvent(event);
	if (!this->isChecked())
	{
		animateToColor(m_normalColor);
	}
}

void GradientButton::mousePressEvent(QMouseEvent* event)
{
    QPushButton::mousePressEvent(event);
    animateToColor(m_clickedColor);
}

void GradientButton::mouseReleaseEvent(QMouseEvent* event)
{
    QPushButton::mouseReleaseEvent(event);
	if (!this->isChecked())
	{
		if (rect().contains(event->pos()))
		{
			animateToColor(m_hoverColor);
		}
		else
		{
			animateToColor(m_normalColor);
		}
	}
}

void GradientButton::onPressed()
{
    animateToColor(m_clickedColor);
}

void GradientButton::onReleased()
{
	if (!this->isChecked())
	{
		animateToColor(m_hoverColor);
	}
}

void GradientButton::animateToColor(const QColor& targetColor)
{
    animation->stop();
    animation->setStartValue(m_gradientColor);
    animation->setEndValue(targetColor);
    animation->start();
}
