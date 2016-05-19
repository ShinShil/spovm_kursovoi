package animation;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;

import javafx.animation.Animation;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.event.EventHandler;
import javafx.geometry.Rectangle2D;
import javafx.scene.Cursor;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.util.Duration;
import player.Player;
import player.crip.Crip;
import scenes.replay.ReplayController;
import scenes.symphony.ISizeSymphonyDraw;

/**
 * animtion when image fly from top to down or from down to top
 * @author ShinShil
 *
 */
public abstract class AnimationOneToOneFly extends AnimationSkill implements ISizeSymphonyDraw {
  private Timeline timeline;
  private ImageView imageView;
  private int towerIndex;

  public AnimationOneToOneFly(Player onWhom, Node where, String name) {
    super(onWhom, where, name);
    timeline = new Timeline();
  }

  public void setImg(String animImgPath) {
    animImgPath = "file:resources/animation/fire7.gif";
  }

  public ImageView getImageView() {
    return imageView;
  }

  /**
   * if crip casted the skill
   * @param crip
   * @throws IOException
   */
  public void startByCrip(Crip crip) throws IOException {
    ImageView cripIv = crip.getImageView();
    Label stPoint = new Label();
    stPoint.setPrefHeight(cripIv.getFitHeight());
    stPoint.setPrefWidth(cripIv.getFitWidth());
    stPoint.setLayoutX(cripIv.getLayoutX());
    stPoint.setLayoutY(cripIv.getLayoutY());
    stPoint.setText(crip.getTowerIndex() + "");
    where = stPoint;
    this.crip = true;
    start();
  }

  @Override
  public void start() throws IOException {
    String actionReplay;
    Label startPoint = (Label) where;
    towerIndex = Integer.parseInt(startPoint.getText()) - 1;
    Image im = new Image(animImgPath);
    imageView = new ImageView(im);
    Rectangle2D viewportRect = new Rectangle2D(0, 0, startPoint.getWidth(), startPoint.getHeight());
    imageView.setViewport(viewportRect);
    imageView.setStyle("-fx-border-radius: 10px");
    int tmpIndex = Integer.parseInt(startPoint.getText());

    if (startPoint.getParent() == null) {
      imageView.setLayoutX((towerIndex + 1) * dummyW + dummyW / 6);
      imageView.setOnMouseClicked(new EventHandler<MouseEvent>() {
        @Override
        public void handle(MouseEvent event) {
          try {
            try {
              stop();
            } catch (InterruptedException | NoSuchMethodException | SecurityException
                | ClassNotFoundException | InstantiationException | IllegalAccessException
                | IllegalArgumentException | InvocationTargetException e) {
              e.printStackTrace();
            }
          } catch (IOException e) {
            e.printStackTrace();
          }
        }
      });
      imageView.setCursor(Cursor.HAND);
      imageView.setLayoutY(startPoint.getLayoutY() + dummyH);
      actionReplay = "crip";
    } else {
      crip = false;
      actionReplay = "cast";
      ReplayController.saveActionLastReplay(actionReplay, name, towerIndex + "");
      imageView.setLayoutX((towerIndex - 1) * dummyW + dummyW / 6);
      imageView.setLayoutY(startPoint.getParent().getLayoutY() - startPoint.getHeight());

    }
    controller.getAnimationPlace().getChildren().add(imageView);
    imageView.toFront();
    if (imageView.getLayoutY() >= startPoint.getHeight() && !crip) {
      imageView.setRotate(180);
      imageView.setLayoutX((tmpIndex - 1) * startPoint.getWidth() - 18);
      timeline = new Timeline(new KeyFrame(Duration.millis(5), new EventHandler<ActionEvent>() {
        @Override
        public void handle(ActionEvent event) {
          try {
            moveUp(imageView, startPoint);
          } catch (IOException | NoSuchMethodException | SecurityException | ClassNotFoundException
              | InstantiationException | IllegalAccessException | IllegalArgumentException
              | InvocationTargetException | InterruptedException e) {
            e.printStackTrace();
          }
        }
      }));
    } else {
      timeline = new Timeline(new KeyFrame(Duration.millis(5), new EventHandler<ActionEvent>() {
        @Override
        public void handle(ActionEvent event) {
          try {
            moveDown(imageView, startPoint);
          } catch (IOException | NoSuchMethodException | SecurityException | ClassNotFoundException
              | InstantiationException | IllegalAccessException | IllegalArgumentException
              | InvocationTargetException | InterruptedException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
          }
        }
      }));
    }
    timeline.setCycleCount(Animation.INDEFINITE);
    timeline.play();
  }



  public AnimationOneToOneFly(String name) {
    super(name);
  }

  public void pause() {
    timeline.stop();
  }

  public void play() {
    timeline.play();
  }

  @Override
  public void end() throws IOException, InterruptedException, NoSuchMethodException,
      SecurityException, ClassNotFoundException, InstantiationException, IllegalAccessException,
      IllegalArgumentException, InvocationTargetException {
    timeline.stop();
    imageView.setVisible(false);
    controller.refreshVals();

    if (onWhom != null) // if the story mode, onWhom = null
      onWhom.effectBySkill(name);
  }

  private void moveUp(ImageView iv, Label label) throws IOException, InterruptedException,
      NoSuchMethodException, SecurityException, ClassNotFoundException, InstantiationException,
      IllegalAccessException, IllegalArgumentException, InvocationTargetException {
    iv.setLayoutY(iv.getLayoutY() - 1);
    if (iv.getLayoutY() <= 0) {
      iv.setVisible(false);
      if (!crip) controller.getSldList().get(towerIndex).removeTopSkill();
      end();
    }
  }

  private void moveDown(ImageView iv, Label label) throws IOException, InterruptedException,
      NoSuchMethodException, SecurityException, ClassNotFoundException, InstantiationException,
      IllegalAccessException, IllegalArgumentException, InvocationTargetException {
    iv.setLayoutY(iv.getLayoutY() + 1);
    if (iv.getLayoutY() >= controller.getAnimationPlace().getHeight() - label.getHeight()) {
      iv.setVisible(false);
      if (!crip) controller.getSldList().get(towerIndex).removeTopSkill();
      end();
    }
  }
}
