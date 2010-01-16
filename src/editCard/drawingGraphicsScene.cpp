/**
 * drawingGraphicsScene.cpp
 * E-Level
 * January 12, 2010
 */
#include "drawingGraphicsScene.h"

DrawingGraphicsScene::DrawingGraphicsScene()
	: QGraphicsScene()
{
	this->painter = new QPainter();
	this->stack = new QUndoStack();
	this->selectMode = false;
}

/**
 * Center a single text box in the middle of the scene
 */
void DrawingGraphicsScene::centerText()
{
	QList<QGraphicsItem*> list = QGraphicsScene::items();
	if(list.size() == 1 && list.at(0)->type() == QGraphicsTextItem::type())
	{
		QGraphicsTextItem* t = (QGraphicsTextItem) list.at(0);
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
		this->painter->pen()->setColor(newColor);
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
		this->painter->pen()->setWidth(width);
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
				foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
					i->mousePressEvent(event);
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
		foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
			i->mouseMoveEvent(event);
	QGraphicsScene::mouseMoveEvent(event);
}

/**
 * Handles mouseRelease events. Emits signal that is there is a release to any listening object/method
 */
void DrawingGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	emit drawMouseRelease(event);
	if(this->selectMode)
		foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
			i->mouseReleaseEvent(event);
	QGraphicsScene::mouseReleaseEvent(event);
	update();
}

void DrawingGraphicsScene::keyPressEvent(QKeyEvent* event)
{
	if(this->selectMode)
		if(event->key() == Qt::Key_Delete)
			this->removeSelected();

	foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
		i->keyPressEvent(event);

//	if(this->drawingItem != NULL)
//		this->drawingItem->keyPressEvent(event);
}


void DrawingGraphicsScene::keyReleaseEvent(QKeyEvent event)
{
	foreach(QGraphicsItem* i, QGraphicsScene::selectedItems())
		i->keyReleaseEvent(event);

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
	importMimeData(event.mimeData(), event.scenePos());
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
void focusInEvent(QFocusEvent* event)
{
	QGraphicsScene::focusInEvent(event);
	emit gainedFocus(true);
}

/**
 * Emits signal that the scene has lost focus
 */
void focusOutEvent(QFocusEvent* event)
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
void updateFont(QFont font)
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
//void DrawingGraphicsScene::setType(DrawingItem* type)
//{
//	if(type == NULL)
//		return;
//
//	QObject::disconnect(this, 0, this->drawingItem, 0); // Disconnect all slots
//
//	this->drawingItem = type->copy(this);
//	this->drawingItem->setParent(this);
//
//	this->setSelectMode(this->drawingItem->type() == DrawingSelectItem::type());
//
//	QObject::connect(this, SIGNAL(drawMousePress(QGraphicsSceneMouseEvent*)), this->drawingItem, SLOT(mousePressEvent(QGraphicsSceneMouseEvent*)));
//	QObject::connect(this, SIGNAL(drawMouseHold(QGraphicsSceneMouseEvent*)), this->drawingItem, SLOT(mouseMoveEvent(QGraphicsSceneMouseEvent*)));
//	QObject::connect(this, SIGNAL(drawMouseRelease(QGraphicsSceneMouseEvent*)), this->drawingItem, SLOT(mouseReleaseEvent(QGraphicsSceneMouseEvent*)));
//	QObject::connect(this->drawingItem, SIGNAL(eventItem(DragDropItem*)), this, SLOT(addDrawEvent(DragDropItem*)));
//}

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
//	if(item.type() == DragDropTextItem.type())
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
void addEvent(QUndoCommand* item)
{
	if(item != NULL && item->isValid() && !this->stack->children()->contains(item))
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
			i->setFlag(Qt::ItemIsSelectable, mode);
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
void DrawingGraphicsScene::importMimeData(QMimeData mimeData, QPointF* pos)
{
	if(mimeData->hasImage())
	{
		QImage image = qvariant_cast<QImage>(mimeData->imageData());
		this->addPixmaptoScene(QPixmap::fromImage(image), pos);
	}
	else if(mimeData->hasText())
	{
//		DragDropTextItem* text = new DragDropTextItem(mimeData->text(), QGraphicsScene::font());
//		text->setSelected(true);
//		text->setPos(pos);
//		addDrawEvent(text);
	}
//	else if(mimeData.type() == DragDropMimeData::type())
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
	return;
}
