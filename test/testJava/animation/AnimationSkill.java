package animation;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

import application.INamedObject;
import javafx.scene.Node;
import javafx.scene.image.ImageView;
import player.BasePlayer;
import player.Player;
import scenes.ISceneController;

/**
 * animaiton for skills
 * should start the animation and handle the end of the animation
 * @author ShinShil
 *
 */
public abstract class AnimationSkill implements INamedObject {

  String name;
  BasePlayer who;
  BasePlayer onWhom;
  double duration;
  String skill;
  Node where; // should use explicit conversation to the label, canvas, image, etc... depends on
              // son's realization
  String animImgPath;
  ISceneController controller;
  boolean crip;

  public AnimationSkill(String name) {
    this.name = name;
  }

  public void setOnWhom(BasePlayer player) {
    this.onWhom = player;
  }

  public AnimationSkill(Player onWhom, Node where, String name) {
    this.name = name;
    this.onWhom = onWhom;
    this.where = null;
  }

  public void setController(ISceneController controller) {
    this.controller = controller;
  }

  public void pause() {

  }

  public void play() {

  }

  public void stop() throws IOException, InterruptedException, NoSuchMethodException,
      SecurityException, ClassNotFoundException, InstantiationException, IllegalAccessException,
      IllegalArgumentException, InvocationTargetException {
    end();
  }

  public ImageView getImageView() {
    return null;
  }

  public void init(Player onWhom, Node where, String name, ISceneController controller) {
    this.onWhom = onWhom;
    this.where = where;
    this.name = name;
    this.controller = controller;
  }

  public abstract void start() throws IOException;

  public abstract void end() throws IOException, InterruptedException, NoSuchMethodException,
      SecurityException, ClassNotFoundException, InstantiationException, IllegalAccessException,
      IllegalArgumentException, InvocationTargetException;

  @Override
  public String getName() {
    return name;
  }
}
