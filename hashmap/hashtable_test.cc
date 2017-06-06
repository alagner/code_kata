#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Hashmap
#include <boost/test/unit_test.hpp>
#include "hashtable.hpp"
#include <cstdint>

struct HashMapFixture {
    customHashtable::hashtable<std::uint16_t, std::uint16_t> ht;
};

BOOST_FIXTURE_TEST_SUITE(simpleAddElements, HashMapFixture)

BOOST_AUTO_TEST_CASE(emptyOnCreation) {
    BOOST_CHECK(ht.size() == 0);
}

BOOST_AUTO_TEST_CASE(increaseSizeWhenAddingElements) {
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

BOOST_FIXTURE_TEST_SUITE(simpleRemoveElements, HashMapFixture)

BOOST_AUTO_TEST_CASE(emptyOnCreation) {
    BOOST_CHECK(ht.size() == 0);
}

BOOST_AUTO_TEST_CASE(increaseSizeWhenAddingElements) {
    ht.put(10, 34);
    BOOST_CHECK(ht.size() == 1);

    ht.put(140, 4);
    BOOST_CHECK(ht.size() == 2);

    ht.put(1, 5);
    BOOST_CHECK(ht.size() == 3);

    ht.put(1, 6);
    BOOST_CHECK(ht.size() == 3);

    ht.remove(1);
    BOOST_CHECK(ht.size() == 2);
    
    ht.remove(140);
    BOOST_CHECK(ht.size() == 1);
}



BOOST_AUTO_TEST_SUITE_END()
