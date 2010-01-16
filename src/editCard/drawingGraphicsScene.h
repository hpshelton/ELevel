/**
 * DrawingGraphicsScene.h
 * E-Level
 * January 12, 2010
 */
#ifndef DRAWINGGRAPHICSSCENE_H_
#define DRAWINGGRAPHICSSCENE_H_

#include <QString>
#include <QGraphicsScene>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class DrawingGraphicsScene : public QGraphicsScene
{
public:
	DrawingGraphicsScene() : QGraphicsScene() {};
	int hashCode();
	QString toString();
	static DrawingGraphicsScene* readFromDisk(QXmlStreamReader* reader) { return new DrawingGraphicsScene(); };
	static void writeToDisk(DrawingGraphicsScene* scene, QXmlStreamWriter* writer) {
		writer->writeStartElement("DrawingGraphicsScene");
		writer->writeEndElement();
	};
};

#endif /* DRAWINGGRAPHICSSCENE_H_ */
