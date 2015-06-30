/*
 * This is part of the FL library, a C++ Bayesian filtering library
 * (https://github.com/filtering-library)
 *
 * Copyright (c) 2014 Jan Issac (jan.issac@gmail.com)
 * Copyright (c) 2014 Manuel Wuthrich (manuel.wuthrich@gmail.com)
 *
 * Max-Planck Institute for Intelligent Systems, AMD Lab
 * University of Southern California, CLMC Lab
 *
 * This Source Code Form is subject to the terms of the MIT License (MIT).
 * A copy of the license can be found in the LICENSE file distributed with this
 * source code.
 */

/**
 * \file discrete_distribution.hpp
 * \date 05/25/2014
 * \author Manuel Wuthrich (manuel.wuthrich@gmail.com)
 * \author Jan Issac (jan.issac@gmail.com)
 */

#ifndef FL__DISTRIBUTION__DISCRETE_DISTRIBUTION_HPP
#define FL__DISTRIBUTION__DISCRETE_DISTRIBUTION_HPP

#include <Eigen/Core>

// std
#include <vector>

#include <fl/util/types.hpp>
#include <fl/util/traits.hpp>
#include <fl/util/assertions.hpp>
#include <fl/distribution/interface/moments.hpp>
#include <fl/distribution/interface/standard_gaussian_mapping.hpp>

namespace fl
{

template <typename Variate, int Locations = Eigen::Dynamic>
class DiscreteDistribution
    : public Moments<typename FirstMomentOf<Variate>::Type>,
      public StandardGaussianMapping<Variate, 1>
{
public:
    typedef DiscreteDistribution<Variate, Locations> This;
    typedef Moments<typename FirstMomentOf<Variate>::Type> MomentsInterface;
    typedef StandardGaussianMapping<Variate,1> StandardGaussianMappingInterface;

    typedef typename MomentsInterface::Variate      Mean;
    typedef typename MomentsInterface::SecondMoment Covariance;
    typedef Eigen::Array<Real,    Locations, 1> Function;
    typedef Eigen::Array<Variate, Locations, 1> LocationArray;
    typedef Eigen::Array<Real,    Locations, 1> CommulativeDistribution;

public:
    /// constructor and destructor *********************************************
    explicit
    DiscreteDistribution(int dim = DimensionOf<Variate>(),
                         int locations = MaxOf<Locations, 1>::value)
        : locations_(locations),
          log_prob_mass_(Function::Zero(locations)),
          cumul_distr_(CommulativeDistribution(locations))
    {
        locations_(0) = Variate::Zero(dim);
    }

    virtual ~DiscreteDistribution() { }

    /// non-const functions ****************************************************

    // set ---------------------------------------------------------------------
    virtual void log_unnormalized_prob_mass(const Function& log_prob_mass)
    {
        // rescale for numeric stability
        log_prob_mass_ = log_prob_mass - log_prob_mass.maxCoeff();

        // copy to prob mass
        prob_mass_ = log_prob_mass_.exp();
        Real sum = prob_mass_.sum();

        // normalize
        prob_mass_ /= sum;
        log_prob_mass_ -= std::log(sum);

        // compute cdf
        cumul_distr_.resize(log_prob_mass_.size());

        cumul_distr_[0] = prob_mass_[0];
        for(int i = 1; i < cumul_distr_.size(); i++)
        {
            cumul_distr_[i] = cumul_distr_[i-1] + prob_mass_[i];
        }

        // resize locations
        locations_.resize(log_prob_mass_.size());
    }

    virtual void delta_log_prob_mass(const Function& delta)
    {
        log_unnormalized_prob_mass(log_prob_mass_ + delta);
    }


    virtual void set_uniform(int new_size = size())
    {
        log_unnormalized_prob_mass(Function::Zero(new_size));
    }

    virtual Variate& location(int i)
    {
        return locations_[i];
    }

    template <typename Distribution>
    void from_distribution(const Distribution& distribution, const int& new_size)
    {
        // we first create a local array to sample to. this way, if this
        // is passed as an argument the locations and pmf are not overwritten
        // while sampling
        LocationArray new_locations(new_size);

        for(int i = 0; i < new_size; i++)
        {
            new_locations[i] = distribution.sample();
        }

        set_uniform(new_size);
        locations_ = new_locations;
    }



    /// const functions ********************************************************

    // sampling ----------------------------------------------------------------
    virtual Variate map_standard_normal(const Real& gaussian_sample) const
    {
        Real uniform_sample =
                0.5 * (1.0 + std::erf(gaussian_sample / std::sqrt(2.0)));

        return map_standard_uniform(uniform_sample);
    }

    virtual Variate map_standard_uniform(const Real& uniform_sample) const
    {
        int i = 0;
        for (i = 0; i < cumul_distr_.size(); ++i)
        {
            if (cumul_distr_[i] >= uniform_sample) break;
        }

        return locations_[i];
    }


    // get ---------------------------------------------------------------------
    virtual const Variate& location(int i) const
    {
        return locations_[i];
    }

    virtual const LocationArray& locations() const
    {
        return locations_;
    }

    virtual Real log_prob_mass(const int& i) const
    {
        return log_prob_mass_(i);
    }

    virtual Function log_prob_mass() const
    {
        return log_prob_mass_;
    }

    virtual Real prob_mass(const int& i) const
    {
        return prob_mass_(i);
    }

    virtual Function prob_mass() const
    {
        return prob_mass_;
    }

    virtual int size() const
    {
        return locations_.size();
    }

    virtual int dimension() const
    {
        return locations_[0].rows();
    }


    // compute properties ------------------------------------------------------
    virtual const Mean& mean() const
    {
        mu_ = Mean::Zero(dimension());

        for(int i = 0; i < locations_.size(); i++)
        {
            mu_ += prob_mass(i) * locations_[i].template cast<Real>();
        }

        return mu_;
    }

    virtual const Covariance& covariance() const
    {
        Mean mu = mean();
        cov_ = Covariance::Zero(dimension(), dimension());
        for(int i = 0; i < locations_.size(); i++)
        {
            Mean delta = (locations_[i].template cast<Real>()-mu);
            cov_ += prob_mass(i) * delta * delta.transpose();
        }

        return cov_;
    }

    virtual Real entropy() const
    {
        return - log_prob_mass_.cwiseProduct(prob_mass_).sum();
    }

    // implements KL(p||u) where p is this distr, and u is the uniform distr
    virtual Real kl_given_uniform() const
    {
        return std::log(Real(size())) - entropy();
    }


protected:
    /// member variables *******************************************************
    LocationArray locations_;

    Function log_prob_mass_;
    Function prob_mass_;
    CommulativeDistribution cumul_distr_;

    mutable Mean mu_;
    mutable Covariance cov_;
};

}

#endif
