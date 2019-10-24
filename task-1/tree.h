#pragma once

#include <memory>



namespace bintree {
    template <typename T>
    struct TNode : public std::enable_shared_from_this<TNode<T>> {
        using SFT = std::enable_shared_from_this<TNode<T>>;
        using TNodeWeakPtr = std::weak_ptr<TNode<T>>;
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;
        
        bool hasLeft() const {
            return bool(left);
        }
        
        bool hasRight() const {
            return bool(right);
        }
        
        bool hasParent() const {
            // Проверка на наличие родителя
            return !parent.expired();
        }
        
        T& getValue() {
            return value;
        }
        
        const T& getValue() const {
            return value;
        }
        
        TNodePtr getLeft() {
            return left;
        }
        
        TNodeConstPtr getLeft() const {
            return left;
        }
        
        TNodePtr getRight() {
            return right;
        }
        
        TNodeConstPtr getRight() const {
            return right;
        }
        
        TNodePtr getParent() {
            // Т.к. parent – weak_ptr, если он ни на что не ссылается (expired),
            // то вернет nullptr, иначе вернет shared_ptr на родителя
            return parent.lock();
        }
        
        TNodeConstPtr getParent() const {
            // - // - 
            return parent.lock();
        }
        
        static TNodePtr createLeaf(T v) {
            // Конструктор в private — make_shared с public
            return TNodePtr(new TNode(v));
        }
        
        static TNodePtr fork(T v, TNodePtr left, TNodePtr right) {
            // Если передавать чистые указатели, то при создании Node на left и right
            // Будут созданы новые shared_ptr со своими управляющими блоками
            // Решение — передавать shared_ptr'ы
            // +
            // Конструктор в private — make_shared с public
            TNodePtr ptr = TNodePtr(new TNode(v, left, right));
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }
        
        TNodePtr replaceLeft(TNodePtr l) {
            // Создается лишний указатель с собственным блоком на Parent-Node
            // Необходимо получить уже существующий, увеличив его счетчик
            setParent(l, SFT::shared_from_this());
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }
        
        TNodePtr replaceRight(TNodePtr r) {
            //      - // -
            setParent(r, SFT::shared_from_this());
            setParent(right, nullptr);
            std::swap(r, right);
            return r;
        }
        
        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }
        
        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }
        
        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }
        
    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        // Для исключения взаимного владения потомок-родитель, только один должен владеть
        // Иначе они будут "вечные"
        // Решение — потомок не должен владеть родителем — значит weak_ptr
        TNodeWeakPtr parent;
        
        TNode(T v)
        : value(v)
        {
        }
        // Теперь left и right — shared_ptr'ы
        TNode(T v, TNodePtr left, TNodePtr right)
        : value(v)
        , left(left)
        , right(right)
        {
        }
        
        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
