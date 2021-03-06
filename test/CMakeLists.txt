
# == Util tests ============================================================== #

fl_add_test(NAME traits            SOURCES utils/traits_test.cpp)
fl_add_test(NAME meta              SOURCES utils/meta_test.cpp)
fl_add_test(NAME options           SOURCES utils/options_test.cpp)
fl_add_test(NAME join              SOURCES utils/join_test.cpp)
fl_add_test(NAME descriptor        SOURCES utils/descriptor_test.cpp)
fl_add_test(NAME scalar_matrix     SOURCES utils/scalar_matrix_test.cpp)


fl_add_test(
    NAME la_square_root
    SOURCES utils/linear_algebra_square_root_test.cpp)

fl_add_test(
    NAME la_smw_inversion
    SOURCES utils/linear_algebra_smw_inversion_test.cpp)

fl_add_test(
    NAME la_is_diagonal
    SOURCES utils/linear_algebra_is_diagonal_test.cpp)

fl_add_test(
    NAME sp_normal_to_uniform
    SOURCES utils/special_functions_normal_to_uniform_test.cpp)

# == observation model tests ================================================= #
fl_add_test(
    NAME    linear_gaussian_sensor
    SOURCES model/sensor/linear_gaussian_sensor_test.cpp)

fl_add_test(
    NAME    linear_uncorrelated_gaussian_sensor
    SOURCES model/sensor/linear_uncorrelated_gaussian_sensor_test.cpp)

fl_add_test(
    NAME    body_tail_sensor
    SOURCES model/sensor/body_tail_sensor_test.cpp)

fl_add_test(
    NAME    joint_sensor_iid
    SOURCES model/sensor/joint_sensor_iid_test.cpp)

# == state transition model tests ============================================ #
fl_add_test(
    NAME    linear_transition
    SOURCES model/transition/linear_transition_test.cpp)

fl_add_test(
    NAME    orientation_transition_function
    SOURCES model/transition/orientation_transition_function_test.cpp)

fl_add_test(
    NAME    binary_transition_density
    SOURCES model/binary_transition_density_test.cpp)

# ==filter interface test ==================================================== #
fl_add_test(
    NAME    filter_interface
    SOURCES filter_interface/filter_interface_test.cpp
            filter_interface/filter_interface_stubs.hpp)

# == distribution tests ====================================================== #
fl_add_test(
    NAME    gaussian_distribution
    SOURCES distribution/gaussian_test.cpp)

fl_add_test(
    NAME    decorrelated_gaussian_distribution
    SOURCES distribution/decorrelated_gaussian_test.cpp)

fl_add_test(
    NAME    discrete_distribution
    SOURCES distribution/discrete_distribution_test.cpp)

fl_add_test(
    NAME    chi_squared_distribution
    SOURCES distribution/chi_squared_distribution_test.cpp)

fl_add_test(
    NAME    t_distribution
    SOURCES distribution/t_distribution_test.cpp)

# == exceptions tests ======================================================== #
fl_add_test(NAME exception
            SOURCES exception/exception_test.cpp)

# == Sigma Point Transforms ================================================== #

fl_add_test(
    NAME        unscented_transform_test
    SOURCES     gaussian_filter/unscented_transform_test.cpp)

# == Gaussian filters tests ================================================== #

fl_add_test(
    NAME gaussian_filter_kalman_filter
    SOURCES typecast.hpp
            gaussian_filter/gaussian_filter_test_suite.hpp
            gaussian_filter/kalman_filter_test.cpp)

fl_add_test(
    NAME    gaussian_filter_unscented_kalman_filter
    SOURCES typecast.hpp
            gaussian_filter/gaussian_filter_test_suite.hpp
            gaussian_filter/unscented_kalman_filter_test.cpp)

fl_add_test(
    NAME    multi_sensor_gaussian_filter
    SOURCES typecast.hpp
            gaussian_filter/gaussian_filter_test_suite.hpp
            gaussian_filter/multi_sensor_gaussian_filter_test.cpp)

fl_add_test(
    NAME    robust_multi_sensor_gaussian_filter
    SOURCES typecast.hpp
            gaussian_filter/gaussian_filter_test_suite.hpp
            gaussian_filter/robust_multi_sensor_gaussian_filter_test.cpp)

## gaussian_filter test
add_subdirectory(gaussian_filter)

fl_add_test(
    NAME    robust_gaussian_filter
    SOURCES typecast.hpp
            gaussian_filter/gaussian_filter_test_suite.hpp
            gaussian_filter/robust_gaussian_filter_test.cpp)

## == Particle filters tests ================================================= #
##catkin_add_gtest(particle_filter_test
##                 particle_filter/particle_filter_test.cpp
##                 gtest_main.cpp)
##target_link_libraries(particle_filter_test
##                      ${catkin_LIBRARIES})

fl_add_test(
    NAME    particle_filter_fixture
    SOURCES particle_filter/particle_filter_fixture_test.cpp)

#fl_add_test(frb_particle_filter_test
#                 particle_filter/frb_particle_filter_test.cpp
#                 gtest_main.cpp)
#target_link_libraries(frb_particle_filter_test
#                      ${catkin_LIBRARIES})


# == require refactoring ===================================================== #


### some quick tests ##
##catkin_add_gtest(some_test
##                 utils/some_test.cpp
##                 gtest_main.cpp)
##target_link_libraries(some_test
##                      ${catkin_LIBRARIES})






#catkin_add_gtest(not_adaptive_test utils/not_adaptive_test.cpp gtest_main.cpp)
#target_link_libraries(not_adaptive_test ${catkin_LIBRARIES})




# ## point_set_test tests ##
# catkin_add_gtest(point_set_test
#                  gaussian_filter/point_set_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(point_set_test
#                       ${catkin_LIBRARIES})



# ## monte_carlo trandform tests ##
## catkin_add_gtest(monte_carlo_transform_test
##                  gaussian_filter/monte_carlo_transform_test.cpp
##                  gtest_main.cpp)
## target_link_libraries(monte_carlo_transform_test
##                       ${catkin_LIBRARIES})



# catkin_add_gtest(joint_distribution_id_test
#                  distribution/joint_distribution_id_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(joint_distribution_id_test ${catkin_LIBRARIES})


# catkin_add_gtest(joint_distribution_iid_test
#                  distribution/joint_distribution_iid_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(joint_distribution_iid_test ${catkin_LIBRARIES})





# catkin_add_gtest(joint_sensor_iid_test
#                  model/joint_sensor_iid_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(joint_sensor_iid_test ${catkin_LIBRARIES})

# catkin_add_gtest(joint_transition_id_test
#                  model/joint_transition_id_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(joint_transition_id_test ${catkin_LIBRARIES})


# catkin_add_gtest(joint_transition_iid_test
#                  model/joint_transition_iid_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(joint_transition_iid_test ${catkin_LIBRARIES})


# Factorized SPKF #
#catkin_add_gtest(gaussian_filter_factorized_test
#                 gaussian_filter/gaussian_filter_factorized_test.cpp
#                 gtest_main.cpp)
#target_link_libraries(gaussian_filter_factorized_test ${catkin_LIBRARIES})







#catkin_add_gtest(adaptive_test
#                 model/adaptive_test.cpp
#                 gtest_main.cpp)
#target_link_libraries(adaptive_test ${catkin_LIBRARIES})


# ## Gaussian filter tests ##
# catkin_add_gtest(gaussian_filter_test
#                  gaussian_filter/gaussian_filter_test.cpp
#                  gaussian_filter/gaussian_filter_stubs.hpp
#                  gtest_main.cpp)
# target_link_libraries(gaussian_filter_test
#                       ${catkin_LIBRARIES})


## Factorized UKF vs. Kalman filter tests ##
# catkin_add_gtest(factorized_ukf_kf_test
#                  factorized_ukf/factorized_ukf_kf_test.cpp
#                  gtest_main.cpp)
# target_link_libraries(factorized_ukf_kf_test
#                       ${catkin_LIBRARIES})
##
## ## Factorized UKF tests ##
# catkin_add_gtest(factorized_ukf_test
##                  factorized_ukf/linear_models_test.cpp
#                  factorized_ukf/partitioned_ut_test.cpp
#                  factorized_ukf/smw_inversion_test.cpp
#                  factorized_ukf/square_root_test.cpp
##                  factorized_ukf/llt_diagonal_test.cpp
#                  factorized_ukf/factorized_ukf_unscented_transform_test.cpp
##                  factorized_ukf/predict_test.cpp
#                  factorized_ukf/factorized_ukf_dummies.hpp
#                  factorized_ukf/factorized_ukf_stubs.hpp
#                  gtest_main.cpp)
# target_link_libraries(factorized_ukf_test
#                       ${PROJECT_NAME_TRACKING_INTERFACE}
#                       ${PROJECT_NAME_TRACKING}
#                       ${catkin_LIBRARIES})
