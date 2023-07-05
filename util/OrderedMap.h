#ifndef UTIL_ORDEREDMAP_H
#define UTIL_ORDEREDMAP_H

#include <QMap>
#include <QList>

#include <map>

template<typename K, typename V>
class OrderedMap {
public:

    class Iterator {
    public:
        Iterator(const typename QList<K>::iterator& iter, QMap<K, V>& map)
            : m_iter(iter), m_map(map) {}

        Iterator& operator++() {
            ++m_iter;
            return *this;
        }

        bool operator==(const Iterator& other) const {
            return m_iter == other.m_iter;
        }

        bool operator!=(const Iterator& other) const {
            return m_iter != other.m_iter;
        }

        V& operator*() {
            return m_map[*m_iter];
        }

    private:
        typename QList<K>::iterator m_iter;
        QMap<K, V>& m_map;
    };

    class ConstIterator {
    public:
        ConstIterator(const typename QList<K>::const_iterator& iter, const QMap<K, V>& map)
            : m_iter(iter), m_map(map) {}

        ConstIterator& operator++() {
            ++m_iter;
            return *this;
        }

        bool operator==(const ConstIterator& other) const {
            return m_iter == other.m_iter;
        }

        bool operator!=(const ConstIterator& other) const {
            return m_iter != other.m_iter;
        }

        const V& operator*() const {
            return m_map[*m_iter];
        }

    private:
        typename QList<K>::const_iterator m_iter;
        const QMap<K, V>& m_map;
    };


    void insert(const K& key, const V& value) {
        if (_map.contains(key)) {
            remove(key);
        }

        _map.insert(key, value);
        _list.append(key);
    }

    void remove(const K& key) {
        _map.remove(key);
        _list.removeAll(key);
    }

    V value(const K& key) const {
        return _map.value(key);
    }

    int size() const {
        return _list.size();
    }

    bool contains(const K& key) const {
        return _map.contains(key);
    }

    V at(int i) const {
        return _map.value(_list.at(i));
    }
    
    Iterator begin() {
        return Iterator(_list.begin(), _map);
    }

    Iterator end() {
        return Iterator(_list.end(), _map);
    }

    ConstIterator begin() const {
        return ConstIterator(_list.begin(), _map);
    }

    ConstIterator end() const {
        return ConstIterator(_list.end(), _map);
    }
    
    std::map<K, V> toStdMap() const {
        return _map.toStdMap();
    }

    QList<K> keys() const {
        return _map.keys();
    }

    void clear() {
        _map.clear();
        _list.clear();
    }

private:
    QMap<K, V> _map;
    QList<K> _list;
};

#endif // UTIL_ORDEREDMAP_H
