#ifndef BRANCHITEM_H
#define BRANCHITEM_H

#include "mapitem.h"

#include <QList>

class QString;
class QGraphicsScene;

class BranchContainer;
class BranchWrapper;
class HeadingContainer;
class ImageContainer;
class Task;
class XLink;

class BranchItem : public MapItem {
  public:
    BranchItem(TreeItem *parent = nullptr);
    virtual ~BranchItem();
    virtual void copy(BranchItem *item);
    virtual BranchItem *parentBranch();

    BranchWrapper *branchWrapper();

    virtual void insertBranch(int pos, BranchItem *branch);
    virtual void insertImage (int pos, ImageItem *image);

    virtual QString saveToDir(const QString &tmpdir, const QString &prefix,
                              const QPointF &offset, QList<XLink *> &tmpXLinks,
                              const bool &exportBoundingBoxes);

    virtual void setHeadingColor(
        QColor color); //! Overloaded from TreeItem to update QGraphicsView

  protected:
    bool scrolled;      // true if all children are scrolled and thus invisible
    bool tmpUnscrolled; // can only be true (temporary) for a scrolled subtree
    bool focusHiddenInt; //! Hidden, because another branch is focused in focus mode
    bool focusOnPathInt; //! Ancestor of the focused branch (temporary during update)

  public:
    void updateTaskFlag();
    void setTask(Task *t);
    Task *getTask();
    Flag *taskFlag();

  private:
    Task *task;
    BranchWrapper *branchWrapperInt;

  public:
    virtual void scroll();
    virtual void unScroll();
    virtual bool toggleScroll(); // scroll or unscroll
    virtual bool isScrolled();   // returns scroll state
    virtual bool hasScrolledParent(
        BranchItem *start = nullptr); // true, if any of the parents is scrolled
    virtual bool tmpUnscroll(
        BranchItem *start = nullptr);   // unscroll scrolled parents temporary e.g.
                                     // during "find" process
    virtual bool resetTmpUnscroll(); // scroll all tmp scrolled parents again
                                     // e.g. when unselecting

  public:
    void setBranchesLayout(const QString &);
    void setImagesLayout(const QString &);
    QColor getBackgroundColor(BranchItem *start, bool checkInnerFrame = true);

  protected:
    int lastSelectedBranchNum;
    int lastSelectedBranchNumAlt;

  public:
    virtual void
    setLastSelectedBranch(); //! Set myself as last selected in parent
    virtual void
    setLastSelectedBranch(int i); //! Set last selected branch directly
    virtual BranchItem *
    getLastSelectedBranch(); //! Returns last selected branch usually
    virtual BranchItem *
    getLastSelectedBranchAlt(); //! Used to return last selected branch left of
                                //! a mapcenter

  public:
    TreeItem *findMapItem(
        QPointF p,
        QList <TreeItem*> excludedItems); //! search map for branches or images. Ignore
                              //! excludeItems, where search is started or which are selected


    void setHideMode(HideTmpMode mode); 
    /*! Hide this branch and its children, if they are neither the focused
        branch \a focusBi, nor one of its children or one of its ancestors.
        Set \a focusBi to nullptr to leave focus mode and show everything again.
        \a insideFocus is \c true, if the parent is the focused branch or one
        of its children and tells the recursion that everything stays visible. */
    void setFocusMode(BranchItem *focusBi, bool insideFocus = false);
    void setFocusOnPath(bool b); //!< Mark ancestor of focused branch (temporary)
    bool isFocusHidden();        //!< Hidden, because another branch is focused
    void updateVisuals();

    BranchContainer *createBranchContainer(
        QGraphicsScene *scene); //! Create classic object in GraphicsView

    BranchContainer* getBranchContainer();
    void unlinkBranchContainer();
    Container* getBranchesContainer();
    Container* getImagesContainer();

  private:
    BranchContainer *branchContainer;

  public:
    void updateContainerStackingOrder();
    void addToBranchesContainer(BranchContainer*);
    void addToImagesContainer(ImageContainer*);
    void repositionContainers();
};

#endif
