// roundprogressbar.cpp
#include "roundprogressbar.h"
#include <QPropertyAnimation>
#include <QDebug>

RoundProgressBar::RoundProgressBar(QWidget *parent) :
    QWidget(parent),
    _value(0),
    _min(0),
    _max(100),
    _precision(0),
    _controlFlags(outterCirle|decorateDot|defaultText),
   _margin(10),  // 初始化边距
  _cornerRadius(10)  // 设置默认圆角值
{
    setdefault(90, true);

    // 设置背景色为黑色
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor("#000000"));
    setPalette(pal);

    // 初始化设置
    shadowColor = QColor(49, 177, 190);
    shadowWidth = 10;
    radiusWidth = 5;
    setOutterBarWidth(13);
    setOutterColor(QColor("#292929"));
    setDefaultTextColor(QColor("#FFFFFF"));

    setShadowWidth(7);    // 更小的光晕扩散
    setRadiusWidth(14);    // 更窄的光晕主体
    setShadowColor(QColor(21, 217, 21));  // RGB 绿色
}

RoundProgressBar::~RoundProgressBar()
{
}
/**
 * @brief 计算绘制区域的矩形
 * @param width 要考虑的线宽
 * @return 返回计算后的矩形区域
 */
QRectF RoundProgressBar::calculateRect(int width) const
{
    // 考虑边距和线宽，确保不会出圈
    int totalMargin = _margin + width;
    int size = qMin(this->width(), this->width()) - 2 * totalMargin;
    return QRectF(-size/2, -size/2, size, size);
}
/**
 * @brief 设置进度条的默认参数
 * @param startAngle 起始角度
 * @param clockWise 是否顺时针方向
 */
void RoundProgressBar::setdefault(int startAngle, bool clockWise)
{
    _startAngle = startAngle;
    _clockWise = clockWise;
}
/**
 * @brief 设置外圈宽度
 * @param width 外圈线宽
 */
void RoundProgressBar::setOutterBarWidth(float width)
{
    _outterBarWidth = width;
    update();
}
/**
 * @brief 设置内圈宽度
 * @param width 内圈线宽
 */
void RoundProgressBar::setInnerBarWidth(float width)
{
    _innerBarWidth = width;
    update();
}
/**
 * @brief 设置进度条的值范围
 * @param min 最小值
 * @param max 最大值
 */
void RoundProgressBar::setRange(float min, float max)
{
    if(max < min) {
        _max = 100;
        _min = 0;
    } else {
        _max = max;
        _min = min;
    }
}
/**
 * @brief 设置进度值(带动画效果)
 * @param value 目标值
 */
void RoundProgressBar::setValue(float value)
{
    QPropertyAnimation* animation = new QPropertyAnimation(this, "_value");
    animation->setDuration(500);
    animation->setStartValue(_value);
    animation->setEndValue(value);
    animation->setEasingCurve(QEasingCurve::OutQuad);
    animation->start();
}

/**
 * @brief 内部设置进度值(动画过程中调用)
 * @param value 当前值
 */
void RoundProgressBar::_setValue(float value)
{
    _value = value;
    update();
}
/**
 * @brief 绘制圆弧通用函数
 * @param painter 画笔
 * @param params 绘制参数(宽度、颜色等)
 * @param rect 绘制区域
 * @param startAngle 起始角度
 * @param spanAngle 跨度角度
 */
void RoundProgressBar::drawCircularArc(QPainter& painter, const DrawParams& params,const QRectF& rect, int startAngle, int spanAngle)
{
    QPen pen;
    pen.setWidth(params.width);
    if (params.isGradient) {
        QLinearGradient gradient(0, 0, 0, rect.height());
        gradient.setColorAt(0, params.color);
        gradient.setColorAt(1, params.endColor);
        pen.setBrush(gradient);
    } else {
        pen.setColor(params.color);
    }

    pen.setCapStyle(Qt::RoundCap);
    painter.setPen(pen);
    painter.drawArc(rect, startAngle, spanAngle);
}
/**
 * @brief 绘制外圈
 * @param painter 画笔
 */
void RoundProgressBar::paintOutterBar(QPainter &painter)
{
    if(!(_controlFlags & outterCirle))
        return;

    DrawParams params{
        _outterBarWidth,
        _outterColor,
        _outterColor,
        false
    };

    QRectF rect = calculateRect(_outterBarWidth);
    drawCircularArc(painter, params, rect, 0, 360 * 16);
}
/**
 * @brief 绘制发光效果的圆弧
 * @param painter 画笔
 * @param radius 半径
 * @param angle 角度
 */
void RoundProgressBar::drawArc(QPainter *painter, int radius, qreal angle)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    int smallradius = radius - radiusWidth;
    int maxRaidus = radius + shadowWidth;
    int minRadius = smallradius - shadowWidth;

    QRadialGradient radialGradient(QPointF(0, 0), maxRaidus);
    QColor color = shadowColor;
    QColor lightColor = shadowColor.lighter(100);

    color.setAlphaF(0);
    radialGradient.setColorAt(0, color);
    radialGradient.setColorAt(minRadius * 1.0 / maxRaidus, color);
    color.setAlphaF(0.5);
    radialGradient.setColorAt(smallradius * 1.0 / maxRaidus, color);

    radialGradient.setColorAt((smallradius + 1) * 1.0 / maxRaidus, lightColor);
    radialGradient.setColorAt((radius -1) * 1.0 / maxRaidus, lightColor);
    radialGradient.setColorAt(radius * 1.0 / maxRaidus, color);
    color.setAlphaF(0);
    radialGradient.setColorAt(1, color);

    painter->setBrush(radialGradient);
    painter->drawPie(-maxRaidus-2, -maxRaidus -2, maxRaidus * 2, maxRaidus * 2, (90+1)* 16, (-angle-3) * 16);
    painter->setRenderHint(QPainter::Antialiasing);  // 开启抗锯齿
    painter->restore();
//    painter->save();
//    painter->setPen(Qt::NoPen);

//    // 调整半径计算
//    int baseRadius = radius;
//    int maxRadius = baseRadius + shadowWidth;
//    int minRadius = baseRadius - shadowWidth/2;  // 减小内圈范围

//    // 创建渐变
//    QRadialGradient radialGradient(QPointF(0, 0), maxRadius);
//    QColor color = shadowColor;
//    QColor lightColor = shadowColor.lighter(120);  // 增加亮度

//    // 调整渐变分布
//    // 中心区域完全透明
//    color.setAlphaF(0);
//    radialGradient.setColorAt(0, color);
//    // 从内向外逐渐增加不透明度
//    color.setAlphaF(0.1);
//    radialGradient.setColorAt(0.4, color);
//    color.setAlphaF(0.3);
//    radialGradient.setColorAt(0.6, color);

//    // 最亮的部分
//    lightColor.setAlphaF(0.7);  // 增加最大不透明度
//    radialGradient.setColorAt(0.8, lightColor);

//    // 边缘渐隐
//    color.setAlphaF(0.3);
//    radialGradient.setColorAt(0.9, color);

//    color.setAlphaF(0);
//    radialGradient.setColorAt(1.0, color);

//    painter->setBrush(radialGradient);

//    // 创建路径
//    QRectF rect(-maxRadius, -maxRadius, maxRadius * 2, maxRadius * 2);
//    QPainterPath arcPath;

//    qreal startAngle = _startAngle;
//    qreal spanAngle = _clockWise ? -angle : angle;

//    // 添加圆弧路径
//    arcPath.arcMoveTo(rect, startAngle);
//    arcPath.arcTo(rect, startAngle, spanAngle);

//    // 创建带圆角的描边
//    QPainterPathStroker stroker;
//    stroker.setWidth(_outterBarWidth * 1.2);  // 稍微增加光晕宽度
//    stroker.setCapStyle(Qt::RoundCap);

//    QPainterPath finalPath = stroker.createStroke(arcPath);

//    // 绘制主要光晕
//    painter->fillPath(finalPath, radialGradient);

//    // 可选：添加额外的发光层
//    painter->setOpacity(0.3);  // 设置整体透明度
//    stroker.setWidth(_outterBarWidth * 2);  // 更宽的外发光
//    QPainterPath outerGlowPath = stroker.createStroke(arcPath);
//    painter->fillPath(outerGlowPath, radialGradient);

//    painter->restore();
}

// 添加设置圆角的方法
void RoundProgressBar::setCornerRadius(int radius)
{
    _cornerRadius = radius;
    update();
}
// 绘制进度条的方法
void RoundProgressBar::drawProgress(QPainter& painter)
{
    if(!(_controlFlags & outterCirle))
        return;

    QRectF rect = calculateRect(_outterBarWidth);

    // 计算进度角度
    float angleSpan = (_value - _min) / (_max - _min) * 360;

    // 设置画笔
    QPen pen;
    pen.setWidth(_outterBarWidth);
    pen.setCapStyle(Qt::RoundCap);  // 设置圆角端点

    // 创建渐变色
    QConicalGradient gradient(0, 0, 90);
    gradient.setColorAt(0, shadowColor);
    gradient.setColorAt(1, shadowColor.lighter(120));

    pen.setBrush(gradient);
    painter.setPen(pen);

    // 绘制进度弧
    painter.drawArc(rect, (_startAngle + (_clockWise ? 0 : angleSpan)) * 16,
                   (_clockWise ? -angleSpan : angleSpan) * 16);
}

/**
 * @brief 绘制文本
 * @param painter 画笔
 * @param text 要绘制的文本
 * @param font 字体
 * @param center 文本中心点
 */
void RoundProgressBar::drawText(QPainter& painter, const QString& text,const QFont& font, const QPointF& center)
{
    painter.setFont(font);
    QFontMetrics fm(font);
    QRectF textRect(center.x() - fm.horizontalAdvance(text)/2,center.y() - fm.height()/2,
                   fm.horizontalAdvance(text),
                   fm.height());
    painter.drawText(textRect, Qt::AlignCenter, text);
}
/**
 * @brief 重写绘制事件
 * @param event 绘制事件
 */
void RoundProgressBar::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    // 然后绘制外圈背景
    paintOutterBar(painter);

    // 绘制光晕效果
    qreal angle = (_value - _min) / (_max - _min) * 360;
    int glowRadius = (qMin(width(), width()) - 3* _margin - _outterBarWidth) / 2 + _outterBarWidth/2;
    drawArc(&painter, glowRadius, angle);


    // 最后绘制进度条
    drawProgress(painter);

    // 绘制文本
    if(_controlFlags & defaultText) {
        painter.setPen(_textColor);

        // 绘制百分比
        QFont percentFont("Microsoft YaHei", 22, QFont::Bold);
        QString percentText = QString::number(_value/_max*100,'f',_precision) + "%";
        drawText(painter, percentText, percentFont, QPointF(0, -20));

        // 绘制状态文本
        QFont statusFont("Microsoft YaHei", 16);
        drawText(painter, "充电中...", statusFont, QPointF(0, 30));
    }
}
/**
 * @brief 重写大小改变事件
 * @param event 大小改变事件
 */
void RoundProgressBar::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    caculateSquare();
}

/**
 * @brief 计算组件的正方形区域
 */
void RoundProgressBar::caculateSquare()
{
    _squareWidth = qMin(width(), width());
    _squareStart = -_squareWidth / 2;
}

/**
 * @brief 设置外圈颜色
 * @param outterColor 外圈颜色
 */
void RoundProgressBar::setOutterColor(const QColor& outterColor)
{
    _outterColor = outterColor;
    update();
}
/**
 * @brief 设置内圈渐变颜色
 * @param startColor 起始颜色
 * @param endColor 结束颜色
 */
void RoundProgressBar::setInnerColor(const QColor& startColor, const QColor& endColor)
{
    _startColor = startColor;
    _endColor = endColor;
    update();
}
/**
 * @brief 设置内圈单色
 * @param startColor 内圈颜色
 */
void RoundProgressBar::setInnerColor(const QColor& startColor)
{
    _startColor = startColor;
    update();
}
/**
 * @brief 设置默认文本颜色
 * @param textColor 文本颜色
 */
void RoundProgressBar::setDefaultTextColor(const QColor& textColor)
{
    _textColor = textColor;
    update();
}
/**
 * @brief 设置控制标志
 * @param flags 控制标志位
 */
void RoundProgressBar::setControlFlags(int flags)
{
    _controlFlags |= flags;
    update();
}
/**
 * @brief 设置数值精度
 * @param precision 小数位数
 */
void RoundProgressBar::setPrecision(int precision)
{
    _precision = precision;
    update();
}
/**
 * @brief 设置发光效果颜色
 * @param color 发光颜色
 */
void RoundProgressBar::setShadowColor(const QColor &color)
{
    shadowColor = color;
    update();
}

/**
 * @brief 设置发光效果宽度
 * @param width 发光宽度
 */
void RoundProgressBar::setShadowWidth(int width)
{
    shadowWidth = width;
    update();
}
/**
 * @brief 设置光晕主体宽度
 * @param width 光晕宽度
 */
void RoundProgressBar::setRadiusWidth(int width)
{
    radiusWidth = width;
    update();
}
