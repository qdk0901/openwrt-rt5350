/*
 * es9038.c
 *
 */

#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/initval.h>
#include <sound/soc.h>
#include <linux/of.h>

/*
 * Note this is a simple chip with no configuration interface, sample rate is
 * determined automatically by examining the Master clock and Bit clock ratios
 */
#define SXX_PCM_RATES  (SNDRV_PCM_RATE_8000)


static struct snd_soc_dai_driver sxx_pcm_codec_dai[] = {
	{
		.name = "sxx-pcm-codec",
		.playback = {
			.stream_name = "sxx-pcm-codec-playback",
			.channels_min = 1,
			.channels_max = 2,
			.rates = SXX_PCM_RATES,
			.formats = SNDRV_PCM_FMTBIT_S16_LE,
		},
        .capture = {
            .stream_name = "sxx-pcm-codec-capture",
            .channels_min = 1,
            .channels_max = 2,
            .rates = SXX_PCM_RATES,
            .formats = SNDRV_PCM_FMTBIT_S16_LE,
        },
	},
};

static struct snd_soc_codec_driver soc_codec_dev_sxx_pcm;

static const struct of_device_id sxx_pcm_codec_match[] = {
	{ .compatible = "ralink,sxx-pcm-codec" },
	{},
};
MODULE_DEVICE_TABLE(of, sxx_pcm_codec_match);

static int sxx_pcm_codec_probe(struct platform_device *pdev)
{
	return snd_soc_register_codec(&pdev->dev,
			&soc_codec_dev_sxx_pcm, sxx_pcm_codec_dai, 1);
}

static int sxx_pcm_codec_remove(struct platform_device *pdev)
{
	snd_soc_unregister_codec(&pdev->dev);
	return 0;
}

static struct platform_driver sxx_pcm_codec_driver = {
	.driver = {
			.name = "sxx-pcm-codec",
			.owner = THIS_MODULE,
            .of_match_table = sxx_pcm_codec_match,
	},

	.probe = sxx_pcm_codec_probe,
	.remove = sxx_pcm_codec_remove,
};

module_platform_driver(sxx_pcm_codec_driver);

MODULE_DESCRIPTION("ASoC PCM driver");
MODULE_AUTHOR("Derek Quan");
MODULE_LICENSE("GPL");
