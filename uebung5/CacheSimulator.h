/* 
 * File:   CacheSimulator.h
 * Author: Richard Fussenegger <rfussenegger.mmt-m2012@fh-salzburg.ac.at>
 * Author: Markus Deutschl <mdeutschl.mmt-m2012@fh-salzburg.ac.at>
 * Author: Elisabeth Lang <elang.mmt-m2012@fh-salzburg.ac.at>
 * Created on December 28, 2012, 9:25 PM
 */

using namespace std;

#ifndef CACHESIMULATOR_H
#define CACHESIMULATOR_H

typedef enum {
    direct_mapped,
    set_assoc,
    full_assoc
} CACHE_ASSOCIATIVITY;

class CacheSimulator {
public:

    /**
     * Create new CacheSimulator instance.
     * 
     * @param size
     *   The size of the cache given in Bytes.
     * @param associativity
     *   The cache associativity policy.
     * @param lineSize
     *   The cache line size given in Bytes.
     * @param lackeyInputFile
     *   Absolute or relative path to lackey trace file.
     */
    CacheSimulator(unsigned size, CACHE_ASSOCIATIVITY associativity, unsigned lineSize) : size(size), associativity(associativity), lineSize(lineSize) {

    }

    /**
     * Change the cache associativity level.
     *
     * @param level
     *   The new cache associativity level.
     * @return
     *   False if the current associativity level is set to direct-mapped. Otherwise the level is set
     *   and true returned.
     */
    boolean setAssociativityLevel(unsigned level) {
        if (this->associativity == direct_mapped) return false;
        this->associativityLevel = level;
        return true;
    }

private:

    /**
     * The size of the cache addresses given in Bit.
     */
    unsigned addressSize; // Bit

    /**
     * The size of the cache given in Bytes.
     */
    unsigned size; // Byte

    /**
     * The cache associativity policy.
     */
    CACHE_ASSOCIATIVITY associativity;

    /**
     * The cache associativity level. Default is 0 (zero), means direct-mapped policy.
     */
    unsigned associativityLevel = 0;

    /**
     * The cache line size given in Bytes..
     */
    unsigned lineSize; // Byte

};

#endif	/* CACHESIMULATOR_H */
