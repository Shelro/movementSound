using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.Kinect;
using System.IO;

namespace SkeletonJoint
{
    public partial class Form1 : Form
    {
        /// <summary>
        /// Width of output drawing
        /// </summary>
        private const float RenderWidth = 640.0f;

        /// <summary>
        /// Height of our output drawing
        /// </summary>
        private const float RenderHeight = 480.0f;

        /// <summary>
        /// Thickness of drawn joint lines
        /// </summary>
        private const int JointThickness = 3;

        /// <summary>
        /// Thickness of body center ellipse
        /// </summary>
        private const int BodyCenterThickness = 10;

        /// <summary>
        /// Thickness of clip edge rectangles
        /// </summary>
        private const double ClipBoundsThickness = 10;

        /// <summary>
        /// Pen used to draw skeleton center point
        /// </summary>
        private readonly Pen centerPointPen = new Pen(Color.Blue);

        /// <summary>
        /// Pen used for drawing joints that are currently tracked
        /// </summary>
        private readonly Pen trackedJointPen =new Pen(Color.Orange);

        /// <summary>
        /// Pen used for drawing joints that are currently inferred
        /// </summary>        
        private readonly Pen inferredJointPen = new Pen(Color.Yellow);

        /// <summary>
        /// Pen used for drawing bones that are currently tracked
        /// </summary>
        private readonly Pen trackedBonePen = new Pen(Brushes.Green, 6);

        /// <summary>
        /// Pen used for drawing bones that are currently inferred
        /// </summary>        
        private readonly Pen inferredBonePen = new Pen(Brushes.Gray, 1);

        /// <summary>
        /// Active Kinect sensor
        /// </summary>
        private KinectSensor sensor;

        /// <summary>
        /// Graphics for skeleton rendering output
        /// </summary>
        private Graphics g;

        /// <summary>
        /// Drawing image that we will display
        /// </summary>
        private Image myImage;//游戏面板背景

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Execute startup tasks
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void Form1_Load(object sender, EventArgs e)
        {
            //Initialize background panel
            myImage = new Bitmap(panel1.Width, panel1.Height);
            // Create the Graphics we'll use for drawing
            this.g = Graphics.FromImage(myImage);

            // Look through all sensors and start the first connected one.
            // This requires that a Kinect is connected at the time of app startup.
            // To make your app robust against plug/unplug, 
            // it is recommended to use KinectSensorChooser provided in Microsoft.Kinect.Toolkit (See components in Toolkit Browser).
            foreach (var potentialSensor in KinectSensor.KinectSensors)
            {
                if (potentialSensor.Status == KinectStatus.Connected)
                {
                    
                    this.label1.Text = "正在检测Kinect传感器...";
                    this.sensor = potentialSensor;
                    //var the sensor 
                    if (null == sensor)
                    {
                        this.ShowDialog();
                    }
                    break;
                }
            }

            if (null != this.sensor)
            {
                // Turn on the skeleton stream to receive skeleton frames
                this.sensor.SkeletonStream.Enable();
                this.sensor.ColorStream.Disable();
                this.sensor.DepthStream.Disable();

                // Add an event handler to be called whenever there is new color frame data
                this.sensor.SkeletonFrameReady += this.SensorSkeletonFrameReady;

                // Start the sensor!
                try
                {
                    this.sensor.Start();
                    this.label1.Text = "Kinect连接成功";
                }
                catch (IOException)
                {
                    this.sensor = null;
                }
            }

            if (null == this.sensor)
            {
                this.label1.Text = "Kinect失去连结，请检查USB或电源";
            }
        }

                /// <summary>
        /// Execute shutdown tasks
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (null != this.sensor)
            {
                this.sensor.Stop();
            }
        }

        /// <summary>
        /// Event handler for Kinect sensor's SkeletonFrameReady event
        /// </summary>
        /// <param name="sender">object sending the event</param>
        /// <param name="e">event arguments</param>
        private void SensorSkeletonFrameReady(object sender, SkeletonFrameReadyEventArgs e)
        {
            Skeleton[] skeletons = new Skeleton[0];

            //Open the Skeleton frame 
            using (SkeletonFrame skeletonFrame = e.OpenSkeletonFrame())
            {
                // check that a frame is available  
                if (skeletonFrame != null)
                {
                    // get the skeleton data
                    skeletons = new Skeleton[skeletonFrame.SkeletonArrayLength];
                    // get the skeletal information in this frame  
                    skeletonFrame.CopySkeletonDataTo(skeletons);
                }
            }
       
                // Draw a transparent background to set the render size
                //g.DrawRectangle(Brushes.Black, null, new Rectangle(0.0, 0.0, RenderWidth, RenderHeight));

                if (skeletons.Length != 0)
                {
                    foreach (Skeleton skel in skeletons)
                    {

                        if (skel.TrackingState == SkeletonTrackingState.Tracked)
                        {
                            g.Clear(this.panel1.BackColor);
                            this.DrawBonesAndJoints(skel, g);
                            //为了界面不闪，将动作以一张张位图的形式显现
                            Graphics gg = panel1.CreateGraphics();
                            gg.DrawImage(myImage, 0, 0);
                        }
                        else if (skel.TrackingState == SkeletonTrackingState.PositionOnly)
                        {
                            g.DrawEllipse(
                            this.centerPointPen,
                            this.SkeletonPointToScreen(skel.Position).X, this.SkeletonPointToScreen(skel.Position).Y,
                            BodyCenterThickness,
                            BodyCenterThickness);
                            Graphics gg = panel1.CreateGraphics();
                            gg.DrawImage(myImage, 0, 0);
                        }
                    }
                }
            }

        /// <summary>
        /// Draws a skeleton's bones and joints
        /// </summary>
        /// <param name="skeleton">skeleton to draw</param>
        /// <param name="g">drawing context to draw to</param>
        private void DrawBonesAndJoints(Skeleton skeleton, Graphics g)
        {
            // Render Torso
            this.DrawBone(skeleton, g, JointType.Head, JointType.ShoulderCenter);
            this.DrawBone(skeleton, g, JointType.ShoulderCenter, JointType.ShoulderLeft);
            this.DrawBone(skeleton, g, JointType.ShoulderCenter, JointType.ShoulderRight);
            this.DrawBone(skeleton, g, JointType.ShoulderCenter, JointType.Spine);
            this.DrawBone(skeleton, g, JointType.Spine, JointType.HipCenter);
            this.DrawBone(skeleton, g, JointType.HipCenter, JointType.HipLeft);
            this.DrawBone(skeleton, g, JointType.HipCenter, JointType.HipRight);

            // Left Arm
            this.DrawBone(skeleton, g, JointType.ShoulderLeft, JointType.ElbowLeft);
            this.DrawBone(skeleton, g, JointType.ElbowLeft, JointType.WristLeft);
            this.DrawBone(skeleton, g, JointType.WristLeft, JointType.HandLeft);

            // Right Arm
            this.DrawBone(skeleton, g, JointType.ShoulderRight, JointType.ElbowRight);
            this.DrawBone(skeleton, g, JointType.ElbowRight, JointType.WristRight);
            this.DrawBone(skeleton, g, JointType.WristRight, JointType.HandRight);

            // Left Leg
            this.DrawBone(skeleton, g, JointType.HipLeft, JointType.KneeLeft);
            this.DrawBone(skeleton, g, JointType.KneeLeft, JointType.AnkleLeft);
            this.DrawBone(skeleton, g, JointType.AnkleLeft, JointType.FootLeft);

            // Right Leg
            this.DrawBone(skeleton, g, JointType.HipRight, JointType.KneeRight);
            this.DrawBone(skeleton, g, JointType.KneeRight, JointType.AnkleRight);
            this.DrawBone(skeleton, g, JointType.AnkleRight, JointType.FootRight);
 
            // Render Joints
            foreach (Joint joint in skeleton.Joints)
            {
                Pen drawPen = null;

                if (joint.TrackingState == JointTrackingState.Tracked)
                {
                    drawPen = this.trackedJointPen;                    
                }
                else if (joint.TrackingState == JointTrackingState.Inferred)
                {
                    drawPen = this.inferredJointPen;                    
                }

                if (drawPen != null)
                {
                    g.DrawEllipse(drawPen,this.SkeletonPointToScreen(joint.Position).X, this.SkeletonPointToScreen(joint.Position).Y, (int)JointThickness, (int)JointThickness);
                }
            }
        }

        /// <summary>
        /// Maps a SkeletonPoint to lie within our render space and converts to Point
        /// </summary>
        /// <param name="skelpoint">point to map</param>
        /// <returns>mapped point</returns>
        private Point SkeletonPointToScreen(SkeletonPoint skelpoint)
        {
            // Convert point to depth space.  
            // We are not using depth directly, but we do want the points in our 640x480 output resolution.
            DepthImagePoint depthPoint = this.sensor.CoordinateMapper.MapSkeletonPointToDepthPoint(skelpoint, DepthImageFormat.Resolution640x480Fps30);
            return new Point(depthPoint.X, depthPoint.Y);
        }

        /// <summary>
        /// Draws a bone line between two joints
        /// </summary>
        /// <param name="skeleton">skeleton to draw bones from</param>
        /// <param name="g">drawing context to draw to</param>
        /// <param name="jointType0">joint to start drawing from</param>
        /// <param name="jointType1">joint to end drawing at</param>
        private void DrawBone(Skeleton skeleton, Graphics g, JointType jointType0, JointType jointType1)
        {
            Joint joint0 = skeleton.Joints[jointType0];
            Joint joint1 = skeleton.Joints[jointType1];

            // If we can't find either of these joints, exit
            if (joint0.TrackingState == JointTrackingState.NotTracked ||
                joint1.TrackingState == JointTrackingState.NotTracked)
            {
                return;
            }

            // Don't draw if both points are inferred
            if (joint0.TrackingState == JointTrackingState.Inferred &&
                joint1.TrackingState == JointTrackingState.Inferred)
            {
                return;
            }

            // We assume all drawn bones are inferred unless BOTH joints are tracked
            Pen drawPen = this.inferredBonePen;
            if (joint0.TrackingState == JointTrackingState.Tracked && joint1.TrackingState == JointTrackingState.Tracked)
            {
                drawPen = this.trackedBonePen;
            }

            g.DrawLine(drawPen, this.SkeletonPointToScreen(joint0.Position), this.SkeletonPointToScreen(joint1.Position));
        }
    }
}