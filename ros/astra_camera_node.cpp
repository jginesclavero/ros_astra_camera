/*
 * Copyright (c) 2013, Willow Garage, Inc.
 * Copyright (c) 2016, Orbbec Ltd.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Willow Garage, Inc. nor the names of its
 *       contributors may be used to endorse or promote products derived from
 *       this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 *      Author: Tim Liu (liuhua@orbbec.com)
 */

#include "astra_camera/astra_driver.h"

int main(int argc, char **argv){

  rclcpp::init(argc, argv);
  rclcpp::Node::SharedPtr n = rclcpp::Node::make_shared("astra_camera");
  rclcpp::Node::SharedPtr pnh = rclcpp::Node::make_shared("astra_camera_");

  size_t width, height, dwidth, dheight;
  double framerate, dframerate;
  astra_wrapper::PixelFormat dformat;
  bool use_ir, use_color, use_depth;
  std::string dformat_str;

  pnh->declare_parameter("use_ir");
  pnh->declare_parameter("use_color");
  pnh->declare_parameter("use_depth");
  pnh->declare_parameter("width");
  pnh->declare_parameter("height");
  pnh->declare_parameter("framerate");
  pnh->declare_parameter("dwidth");
  pnh->declare_parameter("dheight");
  pnh->declare_parameter("dframerate");
  pnh->declare_parameter("dformat");


  pnh->get_parameter_or("use_ir", use_ir, false);
  pnh->get_parameter_or("use_color", use_color, true);
  pnh->get_parameter_or("use_depth", use_depth, true);
  pnh->get_parameter_or("width", width, size_t(1280));
  pnh->get_parameter_or("height", height, size_t(1024));
  pnh->get_parameter_or("framerate", framerate, double(30));
  pnh->get_parameter_or("dwidth", dwidth, size_t(640));
  pnh->get_parameter_or("dheight", dheight, size_t(480));
  pnh->get_parameter_or("dframerate", dframerate, double(30));
  pnh->get_parameter_or("dformat", dformat_str, std::string("1MM"));

  if (dformat_str == "1MM") 
  {
    dformat = astra_wrapper::PixelFormat::PIXEL_FORMAT_DEPTH_1_MM;
  }
  else if (dformat_str == "100UM") 
  {
    dformat = astra_wrapper::PixelFormat::PIXEL_FORMAT_DEPTH_100_UM;
  }
  else 
  {
    std::cerr << "Invalid depth format; must be \"1MM\" or \"100UM\"" << std::endl;
    return false;
  }

  astra_wrapper::AstraDriver drv(
    n,
    pnh,
    width,
    height,
    framerate,
    dwidth,
    dheight,
    dframerate,
    dformat);

  rclcpp::spin(n);

  return 0;
}
