model pipes
  inner Modelica.Mechanics.MultiBody.World world annotation(
    Placement(transformation(origin = {-66, 24}, extent = {{-10, -10}, {10, 10}})));
  Modelica.Mechanics.MultiBody.Joints.Revolute revolute annotation(
    Placement(transformation(origin = {-6, 24}, extent = {{-10, -10}, {10, 10}})));
  Modelica.Mechanics.MultiBody.Parts.Body body annotation(
    Placement(transformation(origin = {40, 24}, extent = {{-10, -10}, {10, 10}})));
  Modelica.Mechanics.MultiBody.Forces.Damper damper annotation(
    Placement(transformation(origin = {-6, 66}, extent = {{-10, -10}, {10, 10}})));
equation
  connect(world.frame_b, revolute.frame_a) annotation(
    Line(points = {{-56, 24}, {-16, 24}}, color = {95, 95, 95}));
  connect(revolute.frame_b, body.frame_a) annotation(
    Line(points = {{4, 24}, {30, 24}}, color = {95, 95, 95}));
  connect(revolute.frame_a, damper.frame_a) annotation(
    Line(points = {{-16, 24}, {-16, 66}}, color = {95, 95, 95}));
  connect(revolute.frame_b, damper.frame_b) annotation(
    Line(points = {{4, 24}, {4, 66}}, color = {95, 95, 95}));
  annotation(
    uses(Modelica(version = "4.0.0")));
end pipes;
