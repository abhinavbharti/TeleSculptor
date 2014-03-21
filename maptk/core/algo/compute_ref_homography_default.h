/*ckwg +5
 * Copyright 2014 by Kitware, Inc. All Rights Reserved. Please refer to
 * KITWARE_LICENSE.TXT for licensing information, or contact General Counsel,
 * Kitware, Inc., 28 Corporate Drive, Clifton Park, NY 12065.
 */

/**
 * \file
 * \brief compute_ref_homography algorithm definition
 */

#ifndef MAPTK_ALGO_COMPUTE_REF_HOMOGRAPHY_DEFAULT_H_
#define MAPTK_ALGO_COMPUTE_REF_HOMOGRAPHY_DEFAULT_H_

#include <maptk/core/core_config.h>

#include <boost/scoped_ptr.hpp>

#include <maptk/core/algo/algorithm.h>
#include <maptk/core/algo/compute_ref_homography.h>
#include <maptk/core/track_set.h>
#include <maptk/core/image_container.h>
#include <maptk/core/homography.h>

namespace maptk
{

namespace algo
{


/// Default impl class for mapping each image to some reference image.
/**
 * This class differs from estimate_homographies in that estimate_homographies
 * simply performs a homography regression from matching feature points. This
 * class is designed to generate different types of homographies from input
 * feature tracks, which can transform each image back to the same coordinate
 * space derived from some initial refrerence image.
 */
class MAPTK_CORE_EXPORT compute_ref_homography_default
  : public algo::algorithm_impl<compute_ref_homography_default, compute_ref_homography>
{
public:

  /// Default Constructor
  compute_ref_homography_default();

  /// Copy Constructor
  compute_ref_homography_default( const compute_ref_homography_default& );

  /// Default Destructor
  ~compute_ref_homography_default();

  /// Return the name of this implementation
  virtual std::string impl_name() const { return "default"; }

  /// Get this algorithm's \link maptk::config_block configuration block \endlink
  /**
   * This base virtual function implementation returns an empty configuration
   * block whose name is set to \c this->type_name.
   *
   * \returns \c config_block containing the configuration for this algorithm
   *          and any nested components.
   */
  virtual config_block_sptr get_configuration() const;

  /// Set this algorithm's properties via a config block
  /**
   * \throws no_such_configuration_value_exception
   *    Thrown if an expected configuration value is not present.
   * \throws algorithm_configuration_exception
   *    Thrown when the algorithm is given an invalid \c config_block or is'
   *    otherwise unable to configure itself.
   *
   * \param config  The \c config_block instance containing the configuration
   *                parameters for this algorithm
   */
  virtual void set_configuration( config_block_sptr config );

  /// Check that the algorithm's currently configuration is valid
  /**
   * This checks solely within the provided \c config_block and not against
   * the current state of the instance. This isn't static for inheritence
   * reasons.
   *
   * \param config  The config block to check configuration of.
   *
   * \returns true if the configuration check passed and false if it didn't.
   */
  virtual bool check_configuration( config_block_sptr config ) const;

  /// Estimate the transformation which maps some frame to a reference frame
  /**
   * Similarly to track_features, this class was designed to be called in
   * an online fashion for each sequential frame.
   *
   * \param [in]   frame_number frame identifier for the current frame
   * \param [in]   tracks the set of all tracked features from the image
   * \param return estimated homography
   */
  virtual f2f_homography_sptr
  estimate( frame_id_t frame_number,
            track_set_sptr tracks ) const;

private:

  /// Class storing internal variables
  class priv;
  boost::scoped_ptr<priv> d_;
};


/// Shared pointer type of base compute_ref_homography algorithm definition class
typedef boost::shared_ptr<compute_ref_homography> compute_ref_homography_sptr;


} // end namespace algo

} // end namespace maptk


#endif // MAPTK_ALGO_COMPUTE_REF_HOMOGRAPHY_DEFAULT_H_