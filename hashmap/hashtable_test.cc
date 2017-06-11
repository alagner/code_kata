#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hashmap_test
#include <boost/test/unit_test.hpp>
#include <cstdint>
#include <boost/mpl/list.hpp>
#include <vector>

#ifndef ADD_EXTRA_TEST_GETTERS
#define ADD_EXTRA_TEST_GETTERS
#include "THashtable.hpp"
#endif //ADD_EXTRA_TEST_GETTERS


typedef boost::mpl::list<int, char, long, short > testTypes;

template <typename T>
struct HashMapFixtureForAdding {
    customHashtable::THashtable<T, std::uint16_t> ht;
};

BOOST_AUTO_TEST_SUITE(putAndRetrieveElements)



BOOST_AUTO_TEST_CASE_TEMPLATE(emptyOnCreation, T, testTypes) {
    HashMapFixtureForAdding<T> a;
    BOOST_CHECK(a.ht.size() == 0);
}


BOOST_AUTO_TEST_CASE_TEMPLATE(addReplaceElementsAndCheckExistence, T, testTypes) {
    HashMapFixtureForAdding<T> a;
    a.ht.put(10, 34);
    BOOST_CHECK(a.ht.size() == 1);

    a.ht.put(140, 4);
    BOOST_CHECK(a.ht.size() == 2);

    a.ht.put(1, 5);
    BOOST_CHECK(a.ht.size() == 3);

    a.ht.put(1, 6);
    BOOST_CHECK(a.ht.size() == 3);


    BOOST_CHECK(a.ht.keyExists(10));
    BOOST_CHECK(a.ht.keyExists(140));
    BOOST_CHECK(a.ht.keyExists(1));
    BOOST_CHECK(!a.ht.keyExists(6));
    BOOST_CHECK(!a.ht.keyExists(8));
}

BOOST_AUTO_TEST_SUITE_END()

template <typename T>
struct HashMapFixtureForGetting {
    customHashtable::THashtable<T, std::uint16_t> ht;
    std::vector<T> keys;
    HashMapFixtureForGetting() {
        ht.put(120, 35);
        ht.put(1, 32);
        ht.put(10, 3);
        ht.put(110, 4);
        keys = {
            static_cast<T>(1),
            static_cast<T>(10),
            static_cast<T>(110),
            static_cast<T>(120)
        };
    }
};


BOOST_AUTO_TEST_SUITE(retrieveElements)

BOOST_AUTO_TEST_CASE_TEMPLATE(getExisting, T, testTypes) {
    HashMapFixtureForGetting<T> a;
    BOOST_CHECK(a.ht.get(1) == 32);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(getKeys, T, testTypes) {
    HashMapFixtureForGetting<T> a;
    std::vector<T> keys= a.ht.getKeys();
    std::sort(keys.begin(), keys.end());
    BOOST_CHECK(keys==a.keys);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(getNonExisting, T, testTypes) {
    HashMapFixtureForGetting<T> a;
    BOOST_CHECK_THROW(a.ht.get(5), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()

template <typename T>
struct HashMapFixtureForRemoval {
    customHashtable::THashtable<T, std::uint16_t> ht;
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
    BOOST_CHECK(!a.ht.keyExists(1));
    BOOST_CHECK(a.ht.keyExists(10));
    BOOST_CHECK(a.ht.keyExists(110));
    BOOST_CHECK(a.ht.keyExists(140));

    a.ht.remove(140);
    BOOST_CHECK(a.ht.size() == 2);
    BOOST_CHECK(!a.ht.keyExists(1));
    BOOST_CHECK(!a.ht.keyExists(140));
    BOOST_CHECK(a.ht.keyExists(10));
    BOOST_CHECK(a.ht.keyExists(110));


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
            customHashtable::THashtable<T, std::uint16_t> ht(8,-2); 
            return ht;
        }


        static auto createWrongHTSizeZero() {
            customHashtable::THashtable<T, std::uint16_t> ht(0,1); 
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

template <typename T>
struct HashMapFixtureForRehash { 
    customHashtable::THashtable<T, std::uint16_t> ht; 
    void addSixElements() {
        for (size_t i=0; i < 6; ++i) {
            ht.put(i, i*2);
        }
    }
    void addAnotherSixElements() {
        for (size_t i=6; i < 12; ++i) {
            ht.put(i, i*2);
        }
    }

};

BOOST_AUTO_TEST_SUITE(rehashingAndResizing)


BOOST_AUTO_TEST_CASE_TEMPLATE(resizeOnAddition, T, testTypes) {
    HashMapFixtureForRehash<T> a;
    BOOST_CHECK(a.ht.getCurrentMaxSize() ==8);
    a.addSixElements();
    BOOST_CHECK(a.ht.getCurrentMaxSize() ==16);
    BOOST_CHECK(a.ht.keyExists(0));
    BOOST_CHECK(a.ht.keyExists(1));
    BOOST_CHECK(a.ht.keyExists(2));
    BOOST_CHECK(a.ht.keyExists(3));
    BOOST_CHECK(a.ht.keyExists(4));
    BOOST_CHECK(a.ht.keyExists(5));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(resizeMoreOnAddition, T, testTypes) {
    HashMapFixtureForRehash<T> a;
    BOOST_CHECK(a.ht.getCurrentMaxSize() == 8);
    a.addSixElements();
    a.addSixElements();
    BOOST_CHECK(a.ht.keyExists(0));
    BOOST_CHECK(a.ht.keyExists(1));
    BOOST_CHECK(a.ht.keyExists(2));
    BOOST_CHECK(a.ht.keyExists(3));
    BOOST_CHECK(a.ht.keyExists(4));
    BOOST_CHECK(a.ht.keyExists(5));
    BOOST_CHECK(a.ht.getCurrentMaxSize() == 16);
    a.addAnotherSixElements();
    BOOST_CHECK(a.ht.getCurrentMaxSize() == 32);
    BOOST_CHECK(a.ht.keyExists(0));
    BOOST_CHECK(a.ht.keyExists(1));
    BOOST_CHECK(a.ht.keyExists(2));
    BOOST_CHECK(a.ht.keyExists(3));
    BOOST_CHECK(a.ht.keyExists(4));
    BOOST_CHECK(a.ht.keyExists(5));
    BOOST_CHECK(a.ht.keyExists(6));
    BOOST_CHECK(a.ht.keyExists(7));
    BOOST_CHECK(a.ht.keyExists(8));
    BOOST_CHECK(a.ht.keyExists(9));
    BOOST_CHECK(a.ht.keyExists(10));
    BOOST_CHECK(a.ht.keyExists(11));

}

    
BOOST_AUTO_TEST_SUITE_END()

#ifdef ADD_EXTRA_TEST_GETTERS
#undef ADD_EXTRA_TEST_GETTERS
#endif //ADD_EXTRA_TEST_GETTERS
