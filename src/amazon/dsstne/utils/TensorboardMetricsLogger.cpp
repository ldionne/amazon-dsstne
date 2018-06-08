/*


   Copyright 2016  Amazon.com, Inc. or its affiliates. All Rights Reserved.

   Licensed under the Apache License, Version 2.0 (the "License"). You may not use this file except in compliance with the License. A copy of the License is located at

   http://aws.amazon.com/apache2.0/

   or in the "license" file accompanying this file. This file is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.
 */

#include <amazon/dsstne/utils/TensorboardMetricsLogger.h>

#include <boost/filesystem.hpp>

#include <cassert>
#include <iostream>
#include <string>


#ifdef DSSTNE_TENSORBOARD_SUPPORT

#include <tensorflow/core/util/events_writer.h>

TensorboardMetricsLogger::TensorboardMetricsLogger(boost::filesystem::path const& logdir)
  : _events_writer(std::make_unique<tensorflow::EventsWriter>(logdir / "events").native())
{
    assert(logdir.is_absolute());
    assert(boost::filesystem::is_directory(logdir));
}

void TensorboardMetricsLogger::scalar(int epoch, std::string const& metric, float value) {
    tensorflow::Event event;
    event.set_step(epoch);
    tensorflow::Summary::Value* summary_value = event.mutable_summary()->add_value();
    summary_value->set_tag(metric);
    summary_value->set_simple_value(value);
    _events_writer->WriteEvent(event);
}

#else // there's no support for Tensorboard

TensorboardMetricsLogger::TensorboardMetricsLogger(boost::filesystem::path const& logdir)
  : _events_writer()
{
    std::cout << "Dsstne was built without support for Tensorboard -- no Tensorboard-compatible logs will be generated" << std::endl;
    assert(logdir.is_absolute());
    assert(boost::filesystem::is_directory(logdir));
}

void TensorboardMetricsLogger::scalar(int, std::string const&, float) { }

#endif

TensorboardMetricsLogger::~TensorboardMetricsLogger() { }
