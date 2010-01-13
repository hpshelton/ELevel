/**
 * DrawingGraphicsScene.h
 * E-Level
 * January 12, 2010
 */
#ifndef DRAWINGGRAPHICSSCENE_H_
#define DRAWINGGRAPHICSSCENE_H_

#include <QString>
#include <QGraphicsScene>

class DrawingGraphicsScene : public QGraphicsScene
{
public:
	int hashCode();
	QString toString();
};

#endif /* DRAWINGGRAPHICSSCENE_H_ */
