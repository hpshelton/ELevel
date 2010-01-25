/**
 * drawingGraphicsScene.cpp
 * E-Level
 * January 12, 2010
 */
#include "drawingGraphicsScene.h"

DrawingGraphicsScene::DrawingGraphicsScene()
	: QGraphicsScene()
{
	this->stack = new QUndoStack();
	this->selectMode = false;

	setPenColor(Qt::black);
	setPenWidth(5);
	QGraphicsScene::setFont(QFont("Times New Roman", 12, 50));
}

/**
 * Center a single text box in the middle of the scene
 */
void DrawingGraphicsScene::centerText()
{
	QList<QGraphicsItem*> list = QGraphicsScene::items();
	if(list.size() == 1 && list.at(0)->type() == QGraphicsTextItem::Type)
	{
		QGraphicsTextItem* t = dynamic_cast<QGraphicsTextItem*>(list.at(0));
		// this->stack->push(new MoveItemCommand(t.pos(), t));
		t->setPos((QGraphicsScene::width() - t->boundingRect().width()) / 2, (QGraphicsScene::height() - t->boundingRect().height()) / 2);
	}
}

/**
 * Set the color of the pen
 *
 * @param newColor
 *        The <code>QColor</code> of the pen
 */
void DrawingGraphicsScene::setPenColor(QColor newColor)
{
	if(newColor.isValid())
		this->pen.setColor(newColor);
}

/**
 * Set the width of the pen
 *
 * @param width
 *        The new pen width
 */
void DrawingGraphicsScene::setPenWidth(int width)
{
	if(width > 0)
		this->pen.setWidth(width);
}

/**
 * Handles mousePress events. Emits signal that is there is a left button click to any listening object/method
 * If there are any <code>QGraphicsItemInterface</code> that are selected, they are unselected in the click, unless
 * currently in select mode
 */
void DrawingGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if(event->button() == Qt::LeftButton)
	{
		emit drawMousePress(event);
		if(this->selectMode)
			if(QGraphicsScene::itemAt(event->scenePos()) != NULL)
				foreach(QGraphicsItem* i, QGraphicsScene::selectedItems());
//					i->mousePressEvent(event);
		QGraphicsScene::mousePressEvent(event);
	}
	update();
}

/**
 * Propagate the double click to the drawing item and pass to super class to allow any background activity
 *
 * @param event
 *        The triggering event
 */
void DrawingGraphicsScene::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
	QGraphicsScene::mouseDoubleClickEvent(event);
	//this->drawingItem->mouseDoubleClickEvent(event);
}

/**
 * Handles mouseMove events. Emits signal that is there is a move to any listening object/method
 */
void DrawingGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	emit drawMouseHold(event);
	if(this->selectMode)
		foreach(QGraphicsItem* i, QGraphicsScene::selectedItems());
//			i->mouseMoveEvent(event);
	QGraphicsScene::mouseMoveEvent(event);
}

/**
 * Handles mouseRelease events. Emits signal that is there is a release to any listening object/method
 */
void DrawingGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	emit drawMouseRelease(event);
	if(this->selectMode)
		foreach(QGraphicsItem* i, QGraphicsScene::selectedItems());
//			i->mouseReleaseEvent(event);
	QGraphicsScene::mouseReleaseEvent(event);
	update();
}

void DrawingGraphicsScene::keyPressEvent(QKeyEvent* event)
{
	if(this->selectMode)
		if(event->key() == Qt::Key_Delete)
			this->removeSelected();

	foreach(QGraphicsItem* i, QGraphicsScene::selectedItems());
//		i->keyPressEvent(event);

//	if(this->drawingItem != NULL)
//		this->drawingItem->keyPressEvent(event);
}


void DrawingGraphicsScene::keyReleaseEvent(QKeyEvent* event)
{
	foreach(QGraphicsItem* i, QGraphicsScene::selectedItems());
//		i->keyReleaseEvent(event);

//	if(this->drawingItem != NULL)
//		this->drawingItem->keyReleaseEvent(event);
}

/**
 * Removing a <code>DragDropTextItem</code> if there is no text in the box
 *
 * @param item
 *        The text item to remove if it doesn't have text
 */
//void DrawingGraphicsScene::itemLostFocus(DragDropTextItem item);
//{
//	if(item->toPlainText().length() == 0)
//	{
//		item->document()->undo();
//		this->stack->push(new RemoveItemCommand(item, this));
//	}
//}

/**
 * Handle the drop event by importing any data contained in the <code>QGraphicsSceneDragDropEvent</code>
 */
void DrawingGraphicsScene::dropEvent(QGraphicsSceneDragDropEvent* event)
{
	importMimeData(event->mimeData(), event->scenePos());
	event->acceptProposedAction();
}

/**
 * Undoes the last element on the stack
 */
void DrawingGraphicsScene::undo()
{
	if(this->hasFocus() && this->stack->canUndo())
			this->stack->undo();
}

/**
 * Redoes the last element on the stack
 */
void DrawingGraphicsScene::redo()
{
	if(this->hasFocus() && this->stack->canRedo())
			this->stack->redo();
}

/**
 * Emits signal that the scene has gained focus
 */
void DrawingGraphicsScene::focusInEvent(QFocusEvent* event)
{
	QGraphicsScene::focusInEvent(event);
	emit gainedFocus(true);
}

/**
 * Emits signal that the scene has lost focus
 */
void DrawingGraphicsScene::focusOutEvent(QFocusEvent* event)
{
	QGraphicsScene::focusOutEvent(event);
	emit lostFocus(false);
	unselectAll(true);
}

/**
 * Set the font associated with the object and update all listening objects of the sent font
 *
 * @param font
 *        The <code>font</code> to be used for all drawing
 */
void DrawingGraphicsScene::updateFont(QFont font)
{
	QGraphicsScene::setFont(font);
	emit fontChange(QGraphicsScene::font());
}

/**
 * Set the current type based on the button that was pressed. Connects the proper slots to those objects
 *
 * @param type
 *        the type of button item that was pressed
 */
void DrawingGraphicsScene::setType(DrawingItem* type)
{
	if(type == NULL)
		return;
//
//	QObject::disconnect(this, 0, this->drawingItem, 0); // Disconnect all slots
//
//	this->drawingItem = type->copy(this);
//	this->drawingItem->setParent(this);
//
//	this->setSelectMode(this->drawingItem->type() == DrawingSelectItem::Type);
//
//	QObject::connect(this, SIGNAL(drawMousePress(QGraphicsSceneMouseEvent*)), this->drawingItem, SLOT(mousePressEvent(QGraphicsSceneMouseEvent*)));
//	QObject::connect(this, SIGNAL(drawMouseHold(QGraphicsSceneMouseEvent*)), this->drawingItem, SLOT(mouseMoveEvent(QGraphicsSceneMouseEvent*)));
//	QObject::connect(this, SIGNAL(drawMouseRelease(QGraphicsSceneMouseEvent*)), this->drawingItem, SLOT(mouseReleaseEvent(QGraphicsSceneMouseEvent*)));
//	QObject::connect(this->drawingItem, SIGNAL(eventItem(DragDropItem*)), this, SLOT(addDrawEvent(DragDropItem*)));
}

/**
 * Add an event to the stack
 *
 * @param item
 *        To be added. only accepted if it is a valid command
 * @return <code>true</code> if the item is pushed on the stack, false otherwise
 */
//bool DrawingGraphicsScene::addDrawEvent(DragDropItem* item)
//{
//	DrawItemCommand* command = NULL;
//	if(item.type() == DragDropTextItem::Type))
//		command = new DrawTextItemCommand(item, this);
//	else
//		command = new DrawItemCommand(item, this);
//
//	if(command != NULL && command->isValid())
//	{
//		this->stack->push(command);
//		return true;
//	}
//	return false;
//}

/**
 * Add a move event to the stack
 *
 * @param item
 *        <code>QUndoCommand</code> to be added. Only accepted if it is a valid command
 */
void DrawingGraphicsScene::addEvent(QUndoCommand* item)
{
	if(item != NULL)
		this->stack->push(item);
}

/**
 * @param selectMode
 *        the selectMode to set
 */
void DrawingGraphicsScene::setSelectMode(bool mode)
{
	if(this->selectMode != mode)
	{
		this->selectMode = mode;
		foreach(QGraphicsItem* i, QGraphicsScene::items())
			i->setFlag(QGraphicsItem::ItemIsSelectable, mode);
	}
}

/**
 * Reads in the MIME data and adds it to the given position
 *
 * @param mimeData
 *        The data to read in
 * @param pos
 *        The position to add the elements
 */
void DrawingGraphicsScene::importMimeData(const QMimeData* mimeData, QPointF pos)
{
	if(mimeData->hasImage())
	{
		QImage image = qvariant_cast<QImage>(mimeData->imageData());
		this->addPixmaptoScene(new QPixmap(QPixmap::fromImage(image)), pos);
	}
	else if(mimeData->hasText())
	{
//		DragDropTextItem* text = new DragDropTextItem(mimeData->text(), QGraphicsScene::font());
//		text->setSelected(true);
//		text->setPos(pos);
//		addDrawEvent(text);
	}
//	else if(mimeData.type() == DragDropMimeData::Type)
//	{
//		List<DragDropItem> items = ((DragDropMimeData) mimeData).getDragDropItem();
//		for(DragDropItem i : items)
//		{
//			if(this.items().contains(i))
//				i = i.copy();
//			this.addDrawEvent(i);
//			i.setFlag(GraphicsItemFlag.ItemIsSelectable, true);
//		}
//	}
	else if(mimeData->hasUrls())
	{
		foreach(QUrl u, mimeData->urls())
		{
			if(!u.isEmpty())
			{
				if(QFile::exists(u.toLocalFile()))
				{
					QPixmap* p = new QPixmap(u.toLocalFile());
					if(p != NULL)
						this->addPixmaptoScene(p, pos);
				}
			}
		}
	}
}

/**
 * Add a pixmap at the given point to the scene
 *
 * @param map
 *        The <code>QPixamp</code> to add
 * @param pos
 *        The position to add the element
 */
void DrawingGraphicsScene::addPixmaptoScene(QPixmap* p, QPointF pos)
{
//	DragDropPixmap* d = new DragDropPixmap(p);
//	d->setPos(pos);
//	d->setFlag(Qt::ItemIsSelectable, true);
//	this->addDrawEvent(d);
}

/**
 * Cut the currently selected item(s) onto the clipboard
 */
void DrawingGraphicsScene::cut(QClipboard* clipboard)
{
	if(!this->selectMode)
		return;

//	DragDropMimeData* data = new DragDropMimeData();
//	foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
//	{
//		if(i->type() == DragDropItem::Type)
//		{
//			data->addDragDrop(dynamic_cast<DragDropItem>(i));
//			this->removeItem(i);
//		}
//	}
//	clipboard.setMimeData(data);
}

/**
 * Copy the currently selected item(s) onto the clipboard
 */
void DrawingGraphicsScene::copy(QClipboard* clipboard)
{
	if(!this->selectMode)
		return;

//	DragDropMimeData* data = new DragDropMimeData();
//	foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
//		if(i->type() == DragDropItem::Type)
//			data->addDragDrop((dynamic_cast<DragDropItem>(i)).copy());
//
//	clipboard.setMimeData(data);
}

/**
 * Select all the items if in select mode
 */
void DrawingGraphicsScene::selectAll()
{
	if(this->selectMode)
		foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
			i->setSelected(true);
}


/**
 * Unselect all the items if in select mode
 *
 * @param ignoreText
 *        TODO
 */
void DrawingGraphicsScene::unselectAll(bool ignoreText)
{
	foreach(QGraphicsItem* i, QGraphicsScene::items())
	{
		i->setSelected(false);
		if(!ignoreText)
		{
			if(i->type() == QGraphicsTextItem::Type)
			{
//				QGraphicsTextItem* t = dynamic_cast<QGraphicsTextItem>(i);
//				t->textCursor().clearSelection();
//				t->setSelected(false);
//				t->setTextInteractionFlags(Qt::NoTextInteraction);
//				t->unsetCursor();
//				t->clearFocus();
//				t->setTextCursor(new QTextCursor(t->document()));
			}
		}
	}
}

/**
 * Get the max height value of all the items
 *
 * @return The max height
 */
int DrawingGraphicsScene::zvalue()
{
	int ret = 0;
	foreach(QGraphicsItem* i, QGraphicsScene::items())
	{
		while(i->zValue() >= ret)
			ret++;
	}
	return ret;
}

/**
 * Serializes the <code>DrawingGraphicsScene</code> to file using the specified <code>ObjectOutputStream</code>
 *
 * @param out
 *        an <code>ObjectOutputStream</code> used to serialize the scene
 * @throws IOException
 */
void DrawingGraphicsScene::writeToDisk(DrawingGraphicsScene* scene, QXmlStreamWriter* writer)
{
	scene->flushUndoStack();
	writer->writeStartElement("DrawingGraphicsScene");
	writer->writeEndElement();
}

/**
 * Deserializes the <code>DrawingGraphicsScene</code> from file using the specified <code>ObjectInputStream</code>
 *
 * @param in
 *        an <code>ObjectInputStream</code> used to deserialize the scene
 */
DrawingGraphicsScene* DrawingGraphicsScene::readFromDisk(QXmlStreamReader* reader)
{
	DrawingGraphicsScene* scene = new DrawingGraphicsScene();
	reader->readNextStartElement();
	while(!reader->isEndElement() && reader->name() == "DrawingGraphicsScene")
	{
		reader->readNext();
		// Read all drawing items in
	//	scene->addItem(item);
	//	dynamic_cast<DragDropItem>(item)->setScene(scene);
	}
}
