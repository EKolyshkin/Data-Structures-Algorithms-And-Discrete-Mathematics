/* Created by Egor Kolyshkin on 03/01/2022 */

#include <memory>
#include <string>

using namespace std;

class Entry;
class TreeNode;

class Index
{
public:
   // CONSTRUCTORS:
   Index();
   ~Index();

   // GETTERS:
   int Find(shared_ptr<string>) const;

   // SETTERS:
   void Insert(shared_ptr<string>, int);
   void Remove(shared_ptr<string>);

private:
   // FIELDS:
   shared_ptr<TreeNode> root;

   // GETTERS:
   shared_ptr<TreeNode> locate(shared_ptr<string>) const;

   // SETTERS:
   void split(shared_ptr<TreeNode>);
   void fixTree(shared_ptr<TreeNode>);
};

class TreeNode
{
public:
   // CONSTRUCTORS:
   TreeNode();
   ~TreeNode();

   // GETTERS:
   bool isEmpty() const;
   bool isLeaf() const;
   bool isTwoNode() const;
   bool isThreeNode() const;
   bool shouldSplit() const;
   bool contains(shared_ptr<string>) const;
   shared_ptr<Entry> get(shared_ptr<string>) const;
   shared_ptr<Entry> getSmall() const;
   shared_ptr<Entry> getMedium() const;
   shared_ptr<Entry> getLarge() const;
   shared_ptr<TreeNode> getA() const;
   shared_ptr<TreeNode> getB() const;
   shared_ptr<TreeNode> getC() const;
   shared_ptr<TreeNode> getD() const;
   shared_ptr<TreeNode> getParent() const;
   shared_ptr<TreeNode> getSuccessor(shared_ptr<string>) const;

   // SETTERS:
   bool insert(shared_ptr<Entry>);
   void setSmall(shared_ptr<Entry>);
   void setMedium(shared_ptr<Entry>);
   void setLarge(shared_ptr<Entry>);
   void setA(shared_ptr<TreeNode>);
   void setB(shared_ptr<TreeNode>);
   void setC(shared_ptr<TreeNode>);
   void setD(shared_ptr<TreeNode>);
   void setParent(shared_ptr<TreeNode>);
   void replace(shared_ptr<TreeNode>, shared_ptr<TreeNode>,
                shared_ptr<TreeNode>);
   void removeItem(shared_ptr<string>);

private:
   // FIELDS:
   shared_ptr<Entry> small, medium, large;
   shared_ptr<TreeNode> a, b, c, d, parent;
};

class Entry
{
public:
   // CONSTRUCTORS:
   Entry(shared_ptr<string>, int);
   Entry();
   ~Entry();

   // GETTERS:
   int compare(shared_ptr<Entry>) const;
   int compare(shared_ptr<string>) const;
   shared_ptr<string> getKey() const;
   int getValue() const;

   // SETTERS:
   void setValue(int);
   void setKey(shared_ptr<string>);

private:
   // FIELDS:
   shared_ptr<string> key;
   int value;
};

Index::Index() {}

Index::~Index() {}

void Index::Remove(shared_ptr<string> key)
{
   shared_ptr<TreeNode> data = locate(key);

   if (!data->contains(key))
   {
      return;
   }

   shared_ptr<TreeNode> leafNode;

   if (!data->isLeaf())
   { // swap with inorder successor
      leafNode = data->getSuccessor(key);
      shared_ptr<string> temp = leafNode->getSmall()->getKey();

      leafNode->getSmall()->setKey(key);
      data->get(key)->setKey(temp);
   }

   leafNode->removeItem(key);

   if (leafNode->isEmpty())
   {
      fixTree(leafNode);
   }
}

void TreeNode::removeItem(shared_ptr<string> key)
{
   if (*key == *getSmall()->getKey())
   {
      setSmall(getMedium());
      setMedium(nullptr);
   }
   else // if key is in medium
   {
      setMedium(nullptr);
   }
}

int Index::Find(shared_ptr<string> key) const
{
   shared_ptr<TreeNode> result = locate(key);
   shared_ptr<Entry> entry = result->get(key);

   if (entry == nullptr)
   {
      return -1;
   }

   return entry->getValue();
}

shared_ptr<TreeNode> Index::locate(shared_ptr<string> key) const
{
   shared_ptr<TreeNode> current = root;

   if (current == nullptr)
   {
      return root;
   }

   while (!current->isLeaf() && !current->contains(key))
   {
      if (current->isThreeNode())
      {
         if (current->getMedium()->compare(key) < 0)
         {
            current = current->getC();
            continue;
         }
      }

      if (current->getSmall()->compare(key) < 0)
      { // two-node NOT at C
         current = current->getB();
      }
      else
      {
         current = current->getA();
      }
   }

   return current;
}

void Index::split(shared_ptr<TreeNode> current)
{
   shared_ptr<TreeNode> p;

   if (current != root)
   {
      p = current->getParent();
   }
   else
   { // create a new root
      root = p = make_shared<TreeNode>();
   }

   shared_ptr<TreeNode> n1 = make_shared<TreeNode>();
   shared_ptr<TreeNode> n2 = make_shared<TreeNode>();
   p->replace(current, n1, n2);
   n1->setParent(p);
   n2->setParent(p);
   n1->setSmall(current->getSmall());
   n2->setSmall(current->getLarge());

   if (!current->isLeaf())
   {
      n1->setA(current->getA());
      n1->setB(current->getB());
      n2->setA(current->getC());
      n2->setB(current->getD());
   }

   p->insert(current->getMedium());

   if (p->shouldSplit())
   {
      split(p);
   }
}

void Index::fixTree(shared_ptr<TreeNode> current)
{
   if (current == root)
   {
      root = nullptr;
   }
   else
   {
      shared_ptr<TreeNode> p = current->getParent();

      if (p->isTwoNode())
      {
      }
   }
}

void Index::Insert(shared_ptr<string> key, int value)
{
   shared_ptr<Entry> newItem = make_shared<Entry>(key, value);
   shared_ptr<TreeNode> current = locate(key);

   if (current->insert(newItem))
   {
      return;
   }
   // insert key into current
   if (current->shouldSplit())
   {
      split(current);
   }
}

TreeNode::TreeNode() {}

TreeNode::~TreeNode() {}

shared_ptr<Entry> TreeNode::getSmall() const
{
   return small;
}

shared_ptr<Entry> TreeNode::getMedium() const
{
   return medium;
}

shared_ptr<Entry> TreeNode::getLarge() const
{
   return large;
}

shared_ptr<TreeNode> TreeNode::getA() const
{
   return a;
}

shared_ptr<TreeNode> TreeNode::getB() const
{
   return b;
}

shared_ptr<TreeNode> TreeNode::getC() const
{
   return c;
}

shared_ptr<TreeNode> TreeNode::getD() const
{
   return d;
}

shared_ptr<TreeNode> TreeNode::getParent() const
{
   return parent;
}

shared_ptr<TreeNode> TreeNode::getSuccessor(shared_ptr<string> key) const
{
   shared_ptr<TreeNode> current;

   if (*key == *small->getKey())
   { // find pointer right of key
      current = getB();
   }
   else
   {
      current = getC();
   }

   while (current->getA() != nullptr)
   { // traverse down to leftmost node
      current = current->getA();
   }

   return current;
}

void TreeNode::setSmall(shared_ptr<Entry> value)
{
   small = value;
}

void TreeNode::setMedium(shared_ptr<Entry> value)
{
   medium = value;
}

void TreeNode::setLarge(shared_ptr<Entry> value)
{
   large = value;
}

void TreeNode::setA(shared_ptr<TreeNode> value)
{
   a = value;
}

void TreeNode::setB(shared_ptr<TreeNode> value)
{
   b = value;
}

void TreeNode::setC(shared_ptr<TreeNode> value)
{
   c = value;
}

void TreeNode::setD(shared_ptr<TreeNode> value)
{
   d = value;
}

void TreeNode::setParent(shared_ptr<TreeNode> value)
{
   parent = value;
}

shared_ptr<Entry> TreeNode::get(shared_ptr<string> key) const
{
   if (small->compare(key) == 0)
   {
      return small;
   }
   if (medium && medium->compare(key) == 0)
   {
      return medium;
   }

   return nullptr;
}

bool TreeNode::contains(shared_ptr<string> key) const
{
   return get(key) != nullptr;
}

bool TreeNode::isThreeNode() const
{
   return small && medium;
}

bool TreeNode::isTwoNode() const
{
   return small && !medium;
}

// all positions full, need to split this node
bool TreeNode::shouldSplit() const
{
   return small && medium && large;
}

bool TreeNode::insert(shared_ptr<Entry> newNode)
{
   if (small->compare(newNode) == 0)
   {
      small = newNode;
      return true;
   }
   if (medium != nullptr && medium->compare(newNode) == 0)
   {
      medium = newNode;
      return true;
   }
   if (medium != nullptr && medium->compare(newNode) < 0)
   {
      large = newNode;
      return false;
   }
   if (medium != nullptr && medium->compare(newNode) > 0)
   {
      large = medium;

      if (small->compare(newNode) < 0)
      {
         medium = newNode;
      }
      else
      {
         medium = small;
         small = newNode;
      }

      return false;
   }
   // medium was nullptr
   if (small->compare(newNode) < 0)
   {
      medium = small;
      small = newNode;
   }
   else
   {
      medium = newNode;
   }

   return false;
}

void TreeNode::replace(shared_ptr<TreeNode> replace,
                       shared_ptr<TreeNode> n1, shared_ptr<TreeNode> n2)
{
   if (replace == a)
   {
      d = c;
      c = b;
      b = n2;
      a = n1;
   }
   else if (replace == b)
   { // a is unchanged
      d = c;
      c = n2;
      b = n1;
   }
   else // if (replace = c)
   {
      d = n2;
      c = n1;
   }
}

bool TreeNode::isEmpty() const
{
   return !small && !medium && !large;
}

bool TreeNode::isLeaf() const
{
   return !a && !b && !c;
}

Entry::Entry(shared_ptr<string> key, int value) : key(key), value(value) {}

Entry::Entry() : value(-1) {}

Entry::~Entry() {}

int Entry::compare(shared_ptr<Entry> other) const
{
   if (other == nullptr || other->getKey() == nullptr)
   {
      throw "error";
   }

   return key->compare(*(other->getKey()));
}

int Entry::compare(shared_ptr<string> other) const
{
   if (other == nullptr)
   {
      throw "error";
   }

   return key->compare(*other);
}

int Entry::getValue() const
{
   return value;
}

void Entry::setValue(int value)
{
   this->value = value;
}

void Entry::setKey(shared_ptr<string> key)
{
   this->key = key;
}

shared_ptr<string> Entry::getKey() const
{
   return key;
}