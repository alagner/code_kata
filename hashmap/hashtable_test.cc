#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hashmap_test
#include <boost/test/unit_test.hpp>
#include "hashtable.hpp"
#include <cstdint>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<int, char, long, short > testTypes;

template <typename T>
struct HashMapFixtureForAdding {
    customHashtable::hashtable<T, std::uint16_t> ht;
};

BOOST_AUTO_TEST_SUITE(putAndRetrieveElements)



BOOST_AUTO_TEST_CASE_TEMPLATE(emptyOnCreation, T, testTypes) {
    HashMapFixtureForAdding<T> a;
    BOOST_CHECK(a.ht.size() == 0);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(addAndReplaceElements, T, testTypes) {
    HashMapFixtureForAdding<T> a;
    a.ht.put(10, 34);
    BOOST_CHECK(a.ht.size() == 1);

    a.ht.put(140, 4);
    BOOST_CHECK(a.ht.size() == 2);

    a.ht.put(1, 5);
    BOOST_CHECK(a.ht.size() == 3);

    a.ht.put(1, 6);
    BOOST_CHECK(a.ht.size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()

template <typename T>
struct HashMapFixtureForGetting {
    customHashtable::hashtable<T, std::uint16_t> ht;
    HashMapFixtureForGetting() {
        ht.put(140, 34);
        ht.put(1, 34);
        ht.put(10, 34);
        ht.put(110, 34);
    }
};


BOOST_AUTO_TEST_SUITE(retrieveElements)

BOOST_AUTO_TEST_CASE_TEMPLATE(getExisting, T, testTypes) {
    HashMapFixtureForGetting<T> a;
    BOOST_CHECK(a.ht.get(1) == 34);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(getNonExisting, T, testTypes) {
    HashMapFixtureForGetting<T> a;
    BOOST_CHECK_THROW(a.ht.get(5), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()

template <typename T>
struct HashMapFixtureForRemoval {
    customHashtable::hashtable<T, std::uint16_t> ht;
    HashMapFixtureForRemoval() {
        ht.put(140, 34);
        ht.put(1, 34);
        ht.put(10, 34);
        ht.put(110, 34);
    }
};


BOOST_AUTO_TEST_SUITE(removeElements)


BOOST_AUTO_TEST_CASE_TEMPLATE(decrementOnElementDeletion, T, testTypes){
    HashMapFixtureForRemoval<T> a;

    BOOST_CHECK(a.ht.size() == 4);

    a.ht.remove(1);
    BOOST_CHECK(a.ht.size() == 3);
    
    a.ht.remove(140);
    BOOST_CHECK(a.ht.size() == 2);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(getNonExisting, T, testTypes) {
    HashMapFixtureForRemoval<T> a;
    BOOST_CHECK_THROW(a.ht.remove(50), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()

template <typename T>
struct wrongHT { 
        wrongHT() {}
        static auto createWrongHTNegativeFactor() {
            customHashtable::hashtable<T, std::uint16_t> ht(8,-2); 
            return ht;
        }


        static auto createWrongHTSizeZero() {
            customHashtable::hashtable<T, std::uint16_t> ht(0,1); 
            return ht;
        }
};

BOOST_AUTO_TEST_SUITE(creationFailure)

BOOST_AUTO_TEST_CASE_TEMPLATE(throwWhenLimitNegative, T, testTypes) {
    BOOST_CHECK_THROW(wrongHT<T>::createWrongHTNegativeFactor(), std::logic_error);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(throwWhenSizeZero, T, testTypes) {
    BOOST_CHECK_THROW(wrongHT<T>::createWrongHTSizeZero(), std::logic_error);
}
    
BOOST_AUTO_TEST_SUITE_END()
