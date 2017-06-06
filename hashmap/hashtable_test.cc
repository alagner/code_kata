#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hashmap_test
#include <boost/test/unit_test.hpp>
#include "hashtable.hpp"
#include <cstdint>

struct HashMapFixtureForAdding {
    customHashtable::hashtable<std::uint16_t, std::uint16_t> ht;
};

BOOST_FIXTURE_TEST_SUITE(putAndRetrieveElements, HashMapFixtureForAdding)

BOOST_AUTO_TEST_CASE(emptyOnCreation) {
    BOOST_CHECK(ht.size() == 0);
}

BOOST_AUTO_TEST_CASE(addAndReplaceElements) {
    ht.put(10, 34);
    BOOST_CHECK(ht.size() == 1);

    ht.put(140, 4);
    BOOST_CHECK(ht.size() == 2);

    ht.put(1, 5);
    BOOST_CHECK(ht.size() == 3);

    ht.put(1, 6);
    BOOST_CHECK(ht.size() == 3);
}

BOOST_AUTO_TEST_SUITE_END()


struct HashMapFixtureForGetting {
    customHashtable::hashtable<std::uint16_t, std::uint16_t> ht;
    HashMapFixtureForGetting() {
        ht.put(140, 34);
        ht.put(1, 34);
        ht.put(10, 34);
        ht.put(110, 34);
    }
};


BOOST_FIXTURE_TEST_SUITE(retrieveElements, HashMapFixtureForGetting)

BOOST_AUTO_TEST_CASE(getExisting) {
    BOOST_CHECK(ht.get(1) == 34);
}

BOOST_AUTO_TEST_CASE(getNonExisting) {
    BOOST_CHECK_THROW(ht.get(5), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()


struct HashMapFixtureForRemoval {
    customHashtable::hashtable<std::uint16_t, std::uint16_t> ht;
    HashMapFixtureForRemoval() {
        ht.put(140, 34);
        ht.put(1, 34);
        ht.put(10, 34);
        ht.put(110, 34);
    }
};


BOOST_FIXTURE_TEST_SUITE(removeElements, HashMapFixtureForRemoval)


BOOST_AUTO_TEST_CASE(decrementOnElementDeletion){

    BOOST_CHECK(ht.size() == 4);

    ht.remove(1);
    BOOST_CHECK(ht.size() == 3);
    
    ht.remove(140);
    BOOST_CHECK(ht.size() == 2);
}

BOOST_AUTO_TEST_CASE(getNonExisting) {
    BOOST_CHECK_THROW(ht.remove(50), std::logic_error);
}

BOOST_AUTO_TEST_SUITE_END()

struct wrongHT { 
        wrongHT() {}
        static auto createWrongHTNegativeFactor() {
            customHashtable::hashtable<std::uint16_t, std::uint16_t> ht(8,-2); 
            return ht;
        }


        static auto createWrongHTSizeZero() {
            customHashtable::hashtable<std::uint16_t, std::uint16_t> ht(0,1); 
            return ht;
        }
};

BOOST_FIXTURE_TEST_SUITE(creationFailure, wrongHT)

BOOST_AUTO_TEST_CASE(throwWhenLimitNegative) {
    BOOST_CHECK_THROW(wrongHT::createWrongHTNegativeFactor(), std::logic_error);
}

BOOST_AUTO_TEST_CASE(throwWhenSizeZero) {
    BOOST_CHECK_THROW(wrongHT::createWrongHTSizeZero(), std::logic_error);
}
    
BOOST_AUTO_TEST_SUITE_END()
